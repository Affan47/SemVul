run()
{
    SPtr<TMsg> msg;
    while ( (!this->isDone()) && !ClntTransMgr().isDone() )
    {
	if (serviceShutdown)
	    ClntTransMgr().shutdown();

#ifdef MOD_CLNT_CONFIRM
        if (linkstateChange) {
          ClntAddrMgr().setIA2Confirm(&linkstates);
          this->resetLinkstate();
        }
#endif

	ClntTransMgr().doDuties();

	unsigned int timeout = ClntTransMgr().getTimeout();

	if (timeout == 0)
	    timeout = 1;

        Log(Debug) << "Sleeping for " << timeout << " second(s)." << LogEnd;
        SPtr<TClntMsg> msg=ClntIfaceMgr().select(timeout);

        if (msg) {
	    int iface = msg->getIface();
	    SPtr<TIfaceIface> ptrIface;
	    ptrIface = ClntIfaceMgr().getIfaceByID(iface);
            Log(Info) << "Received " << msg->getName() << " on " << ptrIface->getName()
		      << "/" << iface	<< hex << ",TransID=0x" << msg->getTransID()
		      << dec << ", " << msg->countOption() << " opts:";
            SPtr<TOpt> ptrOpt;
            msg->firstOption();
            while (ptrOpt = msg->getOption() )
                Log(Cont) << " " << ptrOpt->getOptType();
            Log(Cont) << LogEnd;

            ClntTransMgr().relayMsg(msg);
        }
    }
    Log(Notice) << "Bye bye." << LogEnd;
}
