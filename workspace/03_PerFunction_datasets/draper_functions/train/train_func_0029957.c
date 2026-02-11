ajStrFindNextC(const AjPStr str, ajlong pos1, const char* txt2)
{
    size_t i;
    size_t jpos;
    char *cp;

    jpos = ajCvtSposToPosStart(str->Len, 0, pos1);
    cp = strstr(&str->Ptr[jpos], txt2);
    if(!cp)
        return -1;

    i = cp - str->Ptr;

    return i;
}
