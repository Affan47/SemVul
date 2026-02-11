xmlSecGnuTLSASN1IntegerWrite(const unsigned char * data, size_t len) {
    xmlChar *res = NULL;
    int resLen = 64;
    unsigned long long int val = 0;
    size_t ii = 0;
    int shift = 0;

    xmlSecAssert2(data != NULL, NULL);
    xmlSecAssert2(len <= 9, NULL);


    for(ii = len; ii > 0; --ii, shift += 8) {
        val |= ((unsigned long long)data[ii - 1]) << shift;
    }

    res = (xmlChar*)xmlMalloc(resLen + 1);
    if(res == NULL) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlMalloc",
                    XMLSEC_ERRORS_R_MALLOC_FAILED,
                    "size=%d", (int)resLen);
        return (NULL);
    }

    xmlSecStrPrintf(res, resLen, BAD_CAST "%llu", val);
    return(res);
}
