xmlSecTmplObjectAddManifest(xmlNodePtr objectNode,  const xmlChar *id) {
    xmlNodePtr res;

    xmlSecAssert2(objectNode != NULL, NULL);

    res = xmlSecAddChild(objectNode, xmlSecNodeManifest, xmlSecDSigNs);
    if(res == NULL) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    "xmlSecAddChild",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    "node=%s",
		    xmlSecErrorsSafeString(xmlSecNodeManifest));
	return(NULL);
    }
    if(id != NULL) {
	xmlSetProp(res, xmlSecAttrId, id);
    }
    return(res);
}
