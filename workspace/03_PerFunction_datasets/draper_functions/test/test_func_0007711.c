setPreliminaryFlag(const E_PreliminaryFlag flag)
{
    OFCondition result = EC_IllegalCall;

    if (getDocumentType() != DT_KeyObjectSelectionDocument)
    {
        PreliminaryFlagEnum = flag;
        result = EC_Normal;
    }
    return result;
}
