GetOGRFieldType(const char* pszValue,
                                               const char* pszValueType)
{
    if (!bAutodetectTypes || pszValueType == NULL)
        return OFTString;
    else if (strcmp(pszValueType, "string") == 0)
        return OFTString;
    else if (strcmp(pszValueType, "float") == 0 ||
             strcmp(pszValueType, "currency") == 0)
    {
        if (CPLGetValueType(pszValue) == CPL_VALUE_INTEGER)
            return OFTInteger;
        else
            return OFTReal;
    }
    else if (strcmp(pszValueType, "percentage") == 0)
        return OFTReal;
    else if (strcmp(pszValueType, "date") == 0)
    {
        if (strlen(pszValue) == 4 + 1 + 2 + 1 + 2)
            return OFTDate;
        else
            return OFTDateTime;
    }
    else if (strcmp(pszValueType, "time") == 0)
    {
        return OFTTime;
    }
    else
        return OFTString;
}
