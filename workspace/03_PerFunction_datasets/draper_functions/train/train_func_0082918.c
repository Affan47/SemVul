setCounters()
{
    int iaCnt = 0, pdCnt = 0;
    SrvAddrMgr().firstClient();
    SPtr<TAddrClient> client;
    SPtr<TSrvCfgIface> iface;
    while (client = SrvAddrMgr().getClient()) {


        SPtr<TAddrIA> ia;
        client->firstIA();
        while ( ia=client->getIA() ) {
            iface = getIfaceByID(ia->getIface());
            if (!iface)
                continue;

            SPtr<TAddrAddr> addr;
            ia->firstAddr();
            while ( addr=ia->getAddr() ) {
                iface->addClntAddr(addr->get(), true);
                iaCnt++;
            }
        }


        client->firstPD();
        while (ia = client->getPD() ) {
            iface = getIfaceByID(ia->getIface());
            if (!iface)
                continue;
            SPtr<TAddrPrefix> prefix;
            ia->firstPrefix();
            while ( prefix=ia->getPrefix() ) {
                iface->addClntPrefix(prefix->get(), true);
                pdCnt++;
            }
        }
    }
    Log(Debug) << "Increased pools usage: currently " << iaCnt << " address(es) and " << pdCnt << " prefix(es) are leased." << LogEnd;
}
