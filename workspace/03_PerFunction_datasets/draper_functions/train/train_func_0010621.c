getRandomAddr(SPtr<TDUID> clntDuid,
                                              SPtr<TIPv6Addr> clntAddr,
                                              int iface) {
    SPtr<TSrvCfgIface> ptrIface;
    SPtr<TSrvCfgAddrClass> ptrClass;
    SPtr<TIPv6Addr>    any;

    ptrIface = this->getIfaceByID(iface);
    if (!ptrIface) {
        return 0;
    }

    any = new TIPv6Addr();
    ptrIface->firstAddrClass();
    ptrClass = ptrIface->getAddrClass();
    return ptrClass->getRandomAddr();


}
