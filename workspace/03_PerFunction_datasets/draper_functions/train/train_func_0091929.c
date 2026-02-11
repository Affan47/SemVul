xmlSecTmplEncDataEnsureEncProperties(xmlNodePtr encNode, const xmlChar *id) {
    xmlNodePtr res;

    xmlSecAssert2(encNode != NULL, NULL);

    res = xmlSecFindChild(encNode, xmlSecNodeEncryptionProperties, xmlSecEncNs);
    if(res == NULL) {
	res = xmlSecAddChild(encNode, xmlSecNodeEncryptionProperties, xmlSecEncNs);
	if(res == NULL) {
	    xmlSecError(XMLSEC_ERRORS_HERE,
			NULL,
			"xmlSecAddChild",
			XMLSEC_ERRORS_R_XMLSEC_FAILED,
			"node=%s",
			xmlSecErrorsSafeString(xmlSecNodeEncryptionProperties));
	    return(NULL);
	}
    }

    if(id != NULL) {
	xmlSetProp(res, xmlSecAttrId, id);
    }

    return(res);
}
