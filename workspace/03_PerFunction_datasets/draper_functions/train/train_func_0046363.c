SCleavechannel(CmdSet& Set){
    if(Set.defaultarg.empty())
        return false;
    if(!(((PseuInstance*)parentMethod)->GetWSession()))
    {
        logerror("Invalid Script call: SCleavechannel: WorldSession not valid");
        DEF_RETURN_ERROR;
    }
    ((PseuInstance*)parentMethod)->GetWSession()->GetChannels()->Leave(Set.defaultarg);
    return true;
}
