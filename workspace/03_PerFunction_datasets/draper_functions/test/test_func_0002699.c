relayMsg(SPtr<TClntMsg> msgAnswer)
{
    SPtr<TIfaceIface> ifaceQuestion;
    SPtr<TIfaceIface> ifaceAnswer;


    if (!msgAnswer->check())
        return ;

#ifdef MOD_REMOTE_AUTOCONF
    if (neighborInfoGet(msgAnswer->getTransID())) {
        processRemoteReply(msgAnswer);
        return;
    }
#endif


    bool found = false;
    SPtr<TClntMsg> msgQuestion;
    Transactions.first();
    while(msgQuestion=(Ptr*)Transactions.get()) {
        if (msgQuestion->getTransID()==msgAnswer->getTransID()) {
            found =true;
            if (msgQuestion->getIface()!=msgAnswer->getIface()) {
                ifaceQuestion = ClntIfaceMgr().getIfaceByID(msgQuestion->getIface());
                ifaceAnswer   = ClntIfaceMgr().getIfaceByID(msgAnswer->getIface());
                Log(Warning) << "Reply for transaction 0x" << hex << msgQuestion->getTransID() << dec
                             << " sent on " << ifaceQuestion->getFullName() << " was received on interface "
                             << ifaceAnswer->getFullName() << "." << LogEnd;


                msgAnswer->setIface(msgQuestion->getIface());
            }

            handleResponse(msgQuestion, msgAnswer);
            break;
        }
    }

    if (!found)
    {
        if (!Shutdown)
            Log(Warning) << "Message with wrong transID (0x" << hex << msgAnswer->getTransID() << dec
                         << ") received. Ignoring." << LogEnd;
        else
            Log(Debug) << "Message with transID=0x" << hex << msgAnswer->getTransID() << dec
                       << " received, but ignored during shutdown." << LogEnd;
    }
    ClntCfgMgr().dump();
    ClntAddrMgr().dump();
}
