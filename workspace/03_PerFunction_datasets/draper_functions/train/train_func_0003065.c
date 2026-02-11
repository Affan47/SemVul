ajStrFindNextS(const AjPStr str, ajlong pos1, const AjPStr str2)
{
    size_t i;
    size_t jpos;
    char *cp;

    jpos = ajCvtSposToPosStart(str->Len, 0, pos1);

    cp = strstr(&str->Ptr[jpos], str2->Ptr);

    if(!cp)
        return -1;

    i = cp - str->Ptr;

    return i;
}
