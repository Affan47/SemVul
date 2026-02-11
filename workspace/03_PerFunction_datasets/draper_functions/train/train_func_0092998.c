xmlSecKeyInfoCtxCreate(xmlSecKeysMngrPtr keysMngr) {
    xmlSecKeyInfoCtxPtr keyInfoCtx;
    int ret;


    keyInfoCtx = (xmlSecKeyInfoCtxPtr)xmlMalloc(sizeof(xmlSecKeyInfoCtx));
    if(keyInfoCtx == NULL) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    NULL,
                    XMLSEC_ERRORS_R_MALLOC_FAILED,
                    "size=%d", (int)sizeof(xmlSecKeyInfoCtx));
        return(NULL);
    }

    ret = xmlSecKeyInfoCtxInitialize(keyInfoCtx, keysMngr);
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecKeyInfoCtxInitialize",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        xmlSecKeyInfoCtxDestroy(keyInfoCtx);
        return(NULL);
    }

    return(keyInfoCtx);
}
