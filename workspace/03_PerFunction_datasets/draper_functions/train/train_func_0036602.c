xmlSecIOCallbackCreate(xmlInputMatchCallback matchFunc, xmlInputOpenCallback openFunc,
                       xmlInputReadCallback readFunc, xmlInputCloseCallback closeFunc) {
    xmlSecIOCallbackPtr callbacks;

    xmlSecAssert2(matchFunc != NULL, NULL);


    callbacks = (xmlSecIOCallbackPtr)xmlMalloc(sizeof(xmlSecIOCallback));
    if(callbacks == NULL) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    NULL,
                    XMLSEC_ERRORS_R_MALLOC_FAILED,
                    "sizeof(xmlSecIOCallback)=%d",
                    (int)sizeof(xmlSecIOCallback));
        return(NULL);
    }
    memset(callbacks, 0, sizeof(xmlSecIOCallback));

    callbacks->matchcallback = matchFunc;
    callbacks->opencallback  = openFunc;
    callbacks->readcallback  = readFunc;
    callbacks->closecallback = closeFunc;

    return(callbacks);
}
