getOFStringArray(OFString &stringVal,
                                           OFBool normalize)
{

    OFCondition l_error = getStringValue(stringVal);
    if (l_error.good() && normalize)
        normalizeString(stringVal, !MULTIPART, !DELETE_LEADING, DELETE_TRAILING);
    return l_error;
}
