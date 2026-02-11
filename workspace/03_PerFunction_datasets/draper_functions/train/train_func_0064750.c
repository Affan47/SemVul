doDuties()
{

    SPtr <TClntMsg> msg;
    Transactions.first();
    while(msg=Transactions.get())
    {
        if ((!msg->getTimeout())&&(!msg->isDone())) {
            Log(Info) << "Processing msg (" << msg->getName() << ",transID=0x"
                 << hex << msg->getTransID() << dec << ",opts:";
            SPtr<TOpt> ptrOpt;
            msg->firstOption();
            while (ptrOpt = msg->getOption()) {
                Log(Cont) << " " << ptrOpt->getOptType();
            }
            Log(Cont) << ")" << LogEnd;
            msg->doDuties();
        }
    }


    Transactions.first();
    while (msg = Transactions.get() ) {
        if (msg->isDone())
            Transactions.del();
    }

    if (ClntCfgMgr().inactiveMode())
    {
        SPtr<TClntCfgIface> x;
        x = ClntCfgMgr().checkInactiveIfaces();
        if (x) {
            if (!openSockets(x)) {
                Log(Crit) << "Attempt to bind activates interfaces failed."
                          << " Following operation may be unstable!" << LogEnd;
            }
        }
    }

    removeExpired();
    ClntAddrMgr().doDuties();

    ClntAddrMgr().dump();
    ClntIfaceMgr().dump();
    ClntCfgMgr().dump();

    if (!this->Shutdown && !this->IsDone) {


        checkConfirm();


        checkDecline();


        checkSolicit();


        checkRequest();


        checkRenew();


        checkInfRequest();

#ifdef MOD_REMOTE_AUTOCONF
        checkRemoteSolicits();
#endif

    }


    ClntIfaceMgr().doDuties();

    if (this->Shutdown && !Transactions.count())
        this->IsDone = true;
}
