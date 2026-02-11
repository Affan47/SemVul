xmlSecCryptoDLLibraryConstructGetFunctionsName(const xmlChar* name) {
    static xmlChar tmpl[] = "xmlSecCryptoGetFunctions_%s";
    xmlChar* res;
    int len;

    xmlSecAssert2(name != NULL, NULL);

    len = xmlStrlen(name) + xmlStrlen(tmpl) + 1;
    res = (xmlChar*)xmlMalloc(len + 1);
    if(res == NULL) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    NULL,
                    XMLSEC_ERRORS_R_MALLOC_FAILED,
                    "size=%d", len + 1);
        return(NULL);
    }
    xmlSecStrPrintf(res, len, tmpl, name);

    return(res);
}
