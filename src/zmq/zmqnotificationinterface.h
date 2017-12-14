// Copyright (c) 2015-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_ZMQ_ZMQNOTIFICATIONINTERFACE_H
#define BITCOIN_ZMQ_ZMQNOTIFICATIONINTERFACE_H

#include "validationinterface.h"
#include <map>
#include <string>
#include "../primitives/transaction.h"

class CBlockIndex;
class CZMQAbstractNotifier;

#ifdef ENABLE_WALLET
class CWallet;
#endif

class CZMQNotificationInterface : public CValidationInterface {
public:
    virtual ~CZMQNotificationInterface();

    static CZMQNotificationInterface *Create();

#ifdef ENABLE_WALLET
    void RegisterWallet();
#endif


protected:
    bool Initialize();
    void Shutdown();

    void TransactionAddedToWallet(const CTransactionRef& tx, const uint256 &hashBlock);

    // CValidationInterface
    void SyncTransaction(const CTransaction &tx, const CBlockIndex *pindex,
                         int posInBlock);
    void UpdatedBlockTip(const CBlockIndex *pindexNew,
                         const CBlockIndex *pindexFork, bool fInitialDownload);

private:
    CZMQNotificationInterface();

    void *pcontext;
    std::list<CZMQAbstractNotifier *> notifiers;
};

#endif // BITCOIN_ZMQ_ZMQNOTIFICATIONINTERFACE_H
