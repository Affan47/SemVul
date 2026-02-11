openSockets(SPtr<TClntCfgIface> iface) {

    if (iface->noConfig())
        return true;


    SPtr<TIfaceIface> realIface = ClntIfaceMgr().getIfaceByID(iface->getID());
    if (!realIface) {
	    Log(Error) << "Interface " << iface->getFullName()
		           << " not present in system." << LogEnd;
        return false;
    }
    if (!realIface->flagUp()) {
        Log(Error) << "Interface " << realIface->getFullName()
                   << " is down. Unable to open socket." << LogEnd;
        return false;
    }
    if (!realIface->flagRunning()) {
        Log(Error) << "Interface " << realIface->getFullName()
	           << " is not running." << LogEnd;
        return false;
    }


    char* llAddr;
    realIface->firstLLAddress();
    llAddr=realIface->getLLAddress();
    if (!llAddr) {
        Log(Error) << "Interface " << realIface->getFullName()
	           << " does not have link-layer address. Weird." << LogEnd;
        return false;
    }

    SPtr<TIPv6Addr> addr = new TIPv6Addr(llAddr);


    if (iface->getUnicast()) {
	Log(Notice) << "Creating socket for unicast communication on " << iface->getFullName()
		    << LogEnd;
	SPtr<TIPv6Addr> anyaddr = new TIPv6Addr("::", true);
	if (!realIface->addSocket(anyaddr, DHCPCLIENT_PORT, false, this->BindReuse)) {
	    Log(Crit) << "Unicast socket creation (addr=" << anyaddr->getPlain() << ") on "
		      << iface->getFullName() << " interface failed." << LogEnd;
	    return false;
	}

    }

    Log(Notice) << "Creating socket (addr=" << *addr << ") on "
		<< iface->getFullName() << " interface." << LogEnd;
    if (!realIface->addSocket(addr,DHCPCLIENT_PORT,true, this->BindReuse)) {
        Log(Crit) << "Socket creation (addr=" << *addr << ") on "
		  << iface->getFullName() << " interface failed." << LogEnd;
        return false;
    }

    if (llAddr) {
	    char buf[48];
	    inet_ntop6(llAddr,buf);

	    this->ctrlIface = realIface->getID();
	    strncpy(this->ctrlAddr,buf,48);
    }

    return true;
}
