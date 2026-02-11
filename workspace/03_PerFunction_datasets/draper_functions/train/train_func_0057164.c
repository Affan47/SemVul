xmlSecPtrListCreate(xmlSecPtrListId id) {
    xmlSecPtrListPtr list;
    int ret;

    xmlSecAssert2(id != xmlSecPtrListIdUnknown, NULL);


    list = (xmlSecPtrListPtr)xmlMalloc(sizeof(xmlSecPtrList));
    if(list == NULL) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    xmlSecErrorsSafeString(xmlSecPtrListKlassGetName(id)),
                    NULL,
                    XMLSEC_ERRORS_R_MALLOC_FAILED,
                    "sizeof(xmlSecPtrList)=%d",
                    (int)sizeof(xmlSecPtrList));
        return(NULL);
    }

    ret = xmlSecPtrListInitialize(list, id);
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    xmlSecErrorsSafeString(xmlSecPtrListKlassGetName(id)),
                    "xmlSecPtrListInitialize",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        xmlFree(list);
        return(NULL);
    }

    return(list);
}
