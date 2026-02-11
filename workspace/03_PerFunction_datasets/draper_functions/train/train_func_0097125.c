notifyExpireInfo(TNotifyScriptParams& params, const TSrvAddrMgr::TExpiredInfo& exp,
                                    TAddrIA::TIAType type) {
    stringstream tmp;
    tmp << exp.ia->getIface();
    params.addParam("IFINDEX", tmp.str());

    SPtr<TIfaceIface> iface = SrvIfaceMgr().getIfaceByID(exp.ia->getIface());
    if (iface)
        params.addParam("IFACE", iface->getName());

    if (exp.ia->getSrvAddr())
        params.addParam("REMOTE_ADDR", exp.ia->getSrvAddr()->getPlain());
    switch (type) {
    case TAddrIA::TYPE_IA:
    case TAddrIA::TYPE_TA:
    {
        params.addAddr(exp.addr, 0, 0, "");
        break;
    }
    case TAddrIA::TYPE_PD:
    {
        params.addPrefix(exp.addr, exp.prefixLen, 0, 0);
    }
    break;
    }

    tmp.str("");
    tmp << exp.ia->getIAID();
    params.addParam("IAID", tmp.str());
    params.addParam("SRV_OPTION1", exp.client->getDUID()->getPlain());
}
