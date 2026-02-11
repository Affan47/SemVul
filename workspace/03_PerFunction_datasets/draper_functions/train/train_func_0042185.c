SCSendChatMessage(CmdSet& Set){
    if(!(((PseuInstance*)parentMethod)->GetWSession()))
    {
        logerror("Invalid Script call: SCSendChatMessage: WorldSession not valid");
        DEF_RETURN_ERROR;
    }
    std::stringstream ss;
    SCPDatabaseMgr& dbmgr = ((PseuInstance*)parentMethod)->dbmgr;
    uint32 type=atoi(Set.arg[0].c_str());
    uint32 lang=atoi(Set.arg[1].c_str());

    ss << lang;
    if(ss.str()!=Set.arg[1])
    {
        SCPDatabase *langdb = dbmgr.GetDB("language");
        uint32 dblang = langdb->GetFieldByStringValue("name",Set.arg[1].c_str());
        logdev("looking up language id for lang '%s', found %i",Set.arg[1].c_str(),dblang);

        if(dblang != SCP_INVALID_INT)
            lang = dblang;
    }

    std::string msg=Set.arg[2];
    std::string to=Set.arg[3];
    ((PseuInstance*)parentMethod)->GetWSession()->SendChatMessage(type,lang,msg,to);
    return true;
}
