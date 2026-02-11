xmlSecKeyDataIdsRegister(xmlSecKeyDataId id) {
    int ret;

    xmlSecAssert2(id != xmlSecKeyDataIdUnknown, -1);

    ret = xmlSecPtrListAdd(xmlSecKeyDataIdsGet(), (xmlSecPtr)id);
    if(ret < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    "xmlSecPtrListAdd",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    "dataId=%s",
		    xmlSecErrorsSafeString(xmlSecKeyDataKlassGetName(id)));
        return(-1);
    }

    return(0);
}
