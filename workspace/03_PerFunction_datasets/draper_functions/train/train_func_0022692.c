HandleDebugGetItemValueCommand(char* args)
{
    uint32 guid;
    if (!ExtractUInt32(&args, guid))
        { return false; }

    uint32 field;
    if (!ExtractUInt32(&args, field))
        { return false; }

    char* typeStr = ExtractLiteralArg(&args);
    if (!typeStr && *args)
        { return false; }

    Item* item = m_session->GetPlayer()->GetItemByGuid(ObjectGuid(HIGHGUID_ITEM, guid));
    if (!item)
        { return false; }

    return HandleGetValueHelper(item, field, typeStr);
}
