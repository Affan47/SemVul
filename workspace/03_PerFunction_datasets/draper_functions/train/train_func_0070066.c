HandleDebugGetValueCommand(char* args)
{
    Unit* target = getSelectedUnit();
    if (!target)
    {
        SendSysMessage(LANG_SELECT_CHAR_OR_CREATURE);
        SetSentErrorMessage(true);
        return false;
    }

    uint32 field;
    if (!ExtractUInt32(&args, field))
        { return false; }

    char* typeStr = ExtractLiteralArg(&args);
    if (!typeStr && *args)
        { return false; }

    return HandleGetValueHelper(target, field, typeStr);
}
