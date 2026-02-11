assignAddr(SPtr<TIPv6Addr> addr, uint32_t pref, uint32_t valid, bool quiet) {

    SPtr<TSrvOptIAAddress> optAddr;
    SPtr<TSrvCfgAddrClass> ptrClass;

    ptrClass = SrvCfgMgr().getClassByAddr(Iface, addr);
    if (!ptrClass)
        return false;

    pref = ptrClass->getPref(pref);
    valid = ptrClass->getValid(valid);
    optAddr = new TSrvOptIAAddress(addr, pref, valid, this->Parent);


    if (ptrClass->getAddrParams()) {
	Log(Debug) << "Experimental: addr-params subotion added." << LogEnd;
	optAddr->addOption((Ptr*)ptrClass->getAddrParams());
    }

    SubOptions.append((Ptr*)optAddr);

    SubOptions.append(new TSrvOptStatusCode(STATUSCODE_SUCCESS, "Assigned an address.", Parent));

    Log(Info) << "Client " << ClntDuid->getPlain() << " got " << *addr
	      << " (IAID=" << IAID << ", pref=" << pref << ",valid=" << valid << ")." << LogEnd;


    T1= ptrClass->getT1(T1);
    T2= ptrClass->getT2(T2);


    SrvAddrMgr().addClntAddr(ClntDuid, ClntAddr, Iface, IAID, T1, T2, addr, pref, valid, quiet);
    SrvCfgMgr().addClntAddr(this->Iface, addr);

    return true;
}
