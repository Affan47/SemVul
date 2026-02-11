updateClear_WOSD(XMLClear *newP,XMLClear *oldP)
{
    if (oldP) return updateClear_WOSD(OFconst_cast(XMLSTR, newP->lpszValue),OFconst_cast(XMLSTR, oldP->lpszValue));
    return NULL;
}
