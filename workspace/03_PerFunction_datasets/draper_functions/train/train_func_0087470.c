solicitRequest(SPtr<TSrvMsg> clientMsg, SPtr<TSrvOptIA_PD> queryOpt, SPtr<TSrvCfgIface> ptrIface, bool fake) {


    SPtr<TIPv6Addr> hint = 0;
    if (!queryOpt->countPrefixes()) {
        Log(Notice) << "PD option (with IAPREFIX suboptions missing) received. " << LogEnd;
        hint = new TIPv6Addr();
        this->Prefered = DHCPV6_INFINITY;
        this->Valid    = DHCPV6_INFINITY;
    } else {
        SPtr<TSrvOptIAPrefix> hintPrefix = (Ptr*) queryOpt->getOption(OPTION_IAPREFIX);
        hint  = hintPrefix->getPrefix();
        Log(Info) << "PD: PD option with " << hint->getPlain() << " as a hint received." << LogEnd;
        this->Prefered  = hintPrefix->getPref();
        this->Valid     = hintPrefix->getValid();
    }

    int status;
    if (existingLease()) {

        status = STATUSCODE_SUCCESS;
    } else {

        status = assignPrefix(clientMsg, hint, fake);
    }


    SPtr<TSrvOptStatusCode> ptrStatus;
    if (status==STATUSCODE_SUCCESS) {
        ostringstream tmp;
        tmp << countPrefixes() << " prefix(es) granted.";
        ptrStatus = new TSrvOptStatusCode(STATUSCODE_SUCCESS, tmp.str(),  this->Parent);
    } else {
        ptrStatus = new TSrvOptStatusCode(status,
                                          "Unable to provide any prefixes. Sorry.", this->Parent);
    }
    this->SubOptions.append((Ptr*)ptrStatus);
    return;
}
