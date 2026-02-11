appendVendorSpec(SPtr<TDUID> duid, int iface, int vendor, SPtr<TSrvOptOptionRequest> reqOpt)
{
    reqOpt->delOption(OPTION_VENDOR_OPTS);

    SPtr<TSrvCfgIface> ptrIface=SrvCfgMgr().getIfaceByID(iface);
    if (!ptrIface) {
	Log(Error) << "Unable to find interface with ifindex=" << iface << LogEnd;
	return false;
    }

    Log(Debug) << "Client requested vendor-spec. info (vendor=" << vendor
               << ")." << LogEnd;

    SPtr<TSrvCfgOptions> ex = ptrIface->getClientException(duid, true);
    SPtr<TOptVendorSpecInfo> vs;
    List(TOptVendorSpecInfo) vsLst;

    if (ex) {
        vsLst = ex->getVendorSpecLst(vendor);
    } else {
        vsLst = ptrIface->getVendorSpecLst(vendor);
    }


    if (!vsLst.count())
        vsLst = ptrIface->getVendorSpecLst(vendor);

    if (vsLst.count()) {
        vsLst.first();
        while (vs=vsLst.get())
        {
            Options.push_back( (Ptr*)vs);
        }
        return true;
    }

    Log(Debug) << "Unable to find suitable vendor-specific info option." << LogEnd;
    return false;
}
