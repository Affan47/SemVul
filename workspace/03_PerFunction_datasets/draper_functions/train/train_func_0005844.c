check(bool clntIDmandatory, bool srvIDmandatory) {
    bool status = TMsg::check(clntIDmandatory, srvIDmandatory);

    SPtr<TSrvOptServerIdentifier> optSrvID = (Ptr*) this->getOption(OPTION_SERVERID);
    if (optSrvID) {
        if ( !( *(SrvCfgMgr().getDUID()) == *(optSrvID->getDUID()) ) ) {
            Log(Debug) << "Wrong ServerID value detected. This message is not for me. Message ignored." << LogEnd;
            return false;
        }
    }
    return status;
}
