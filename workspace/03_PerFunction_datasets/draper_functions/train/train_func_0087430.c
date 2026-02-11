existingLease() {
    SPtr<TAddrClient> client = SrvAddrMgr().getClient(ClntDuid);
    if (!client)
        return false;
    SPtr<TAddrIA> pd = client->getPD(IAID);
    if (!pd)
        return false;
    if (!pd->getPrefixCount())
        return false;

    SPtr<TAddrPrefix> prefix;
    pd->firstPrefix();
    while (prefix = pd->getPrefix()) {
        Log(Debug) << "Assinging existing lease: prefix=" << prefix->get()->getPlain() << "/" << prefix->getLength()
                   << ", pref=" << prefix->getPref() << ", valid=" << prefix->getValid() << LogEnd;
        SPtr<TOpt> optPrefix = new TSrvOptIAPrefix(prefix->get(), prefix->getLength(),
                                                   prefix->getPref(), prefix->getValid(), this->Parent);
        SubOptions.append((Ptr*)optPrefix);
    }

    T1 = pd->getT1();
    T2 = pd->getT2();

    return true;
}
