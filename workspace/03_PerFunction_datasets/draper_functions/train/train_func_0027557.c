isClntSupported(SPtr<TSrvMsg> msg) {
    int iface=msg->getIface();
    SPtr<TIPv6Addr> clntAddr = msg->getAddr();

    SPtr<TOpt> opt = msg->getOption(OPTION_CLIENTID);
    SPtr<TDUID> duid;
    if (!opt) {

        duid = new TDUID("", 0);
    } else {
        SPtr<TSrvOptClientIdentifier> clientId = (Ptr*) opt;
        duid = clientId->getDUID();
    }

    SPtr<TSrvCfgIface> ptrIface;
    firstIface();
    while((ptrIface=getIface())&&(ptrIface->getID()!=iface)) ;


    if (this->stateless())
        return true;

    int classCnt = 0;
    if (ptrIface)
    {
        SPtr<TSrvCfgAddrClass> ptrClass;
        ptrIface->firstAddrClass();
        while(ptrClass=ptrIface->getAddrClass()) {
            if (ptrClass->clntSupported(duid,clntAddr))
                return true;
            classCnt++;
        }

        SPtr<TSrvCfgPD> pd;
        ptrIface->firstPD();
        while ( pd=ptrIface->getPD() ) {
            if (pd->clntSupported(duid, clntAddr, msg))
                return true;
            classCnt++;
        }
    }
    if (!classCnt) {
        Log(Warning) << "There are no address class defined on the " << ptrIface->getFullName()
                     << ". Maybe you are trying to configure clients on cascade relay interface? "
                     << "If that is so, please define separate class on this interface, too." << LogEnd;
    }
    return false;
}
