SCGetObjectValue(CmdSet &Set)
{
    WorldSession *ws = ((PseuInstance*)parentMethod)->GetWSession();
    if(!ws)
    {
        logerror("Invalid Script call: SCGetObjectValue: WorldSession not valid");
        DEF_RETURN_ERROR;
    }

    uint64 guid = DefScriptTools::toUint64(Set.defaultarg);
    Object *o = ws->objmgr.GetObj(guid);
    if(o)
    {
        uint32 v = (uint32)DefScriptTools::toUint64(Set.arg[0]);
        if(v > o->GetValuesCount())
        {
            logerror("SCGetObjectValue ["I64FMTD", type %u]: invalid value index: %u",guid,o->GetTypeId(),v);
            return "";
        }
        else
        {
            if(DefScriptTools::stringToLower(Set.arg[1]) == "f")
                return toString((ldbl)o->GetFloatValue((UpdateFieldName)v));
            else if(DefScriptTools::stringToLower(Set.arg[1]) == "i64")
                return toString(o->GetUInt64Value((UpdateFieldName)v));
            else
                return toString((uint64)o->GetUInt32Value((UpdateFieldName)v));
        }
    }
    return "";
}
