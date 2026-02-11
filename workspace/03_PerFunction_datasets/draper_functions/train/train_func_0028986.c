xmlSecNssAppKeyCertLoadMemory(xmlSecKeyPtr key, const xmlSecByte* data, xmlSecSize dataSize, xmlSecKeyDataFormat format) {
    SECItem secItem;
    int ret;

    xmlSecAssert2(key != NULL, -1);
    xmlSecAssert2(data != NULL, -1);
    xmlSecAssert2(format != xmlSecKeyDataFormatUnknown, -1);


    memset(&secItem, 0, sizeof(secItem));
    ret = xmlSecNssAppCreateSECItem(&secItem, data, dataSize);
    if(ret < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    "xmlSecNssAppCreateSECItem",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	return(-1);
    }

    ret = xmlSecNssAppKeyCertLoadSECItem(key, &secItem, format);
    if(ret < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    "xmlSecNssAppKeyCertLoadSECItem",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	SECITEM_FreeItem(&secItem, PR_FALSE);
	return(-1);
    }

    SECITEM_FreeItem(&secItem, PR_FALSE);
    return(0);
}
