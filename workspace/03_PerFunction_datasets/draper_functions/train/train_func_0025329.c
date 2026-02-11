xmlSecQName2IntegerNodeRead(xmlSecQName2IntegerInfoConstPtr info, xmlNodePtr node, int* intValue) {
    xmlChar* content = NULL;
    int ret;

    xmlSecAssert2(info != NULL, -1);
    xmlSecAssert2(node != NULL, -1);
    xmlSecAssert2(intValue != NULL, -1);

    content = xmlNodeGetContent(node);
    if(content == NULL) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    "xmlNodeGetContent",
	    	    XMLSEC_ERRORS_R_XML_FAILED,
		    "node=%s",
		    xmlSecErrorsSafeString(node->name));
	return(-1);
    }


    ret = xmlSecQName2IntegerGetIntegerFromString(info, node, content, intValue);
    if(ret < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    "xmlSecQName2IntegerGetIntegerFromString",
	    	    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    "node=%s,value=%s",
		    xmlSecErrorsSafeString(node->name),
                    xmlSecErrorsSafeString(content));
        xmlFree(content);
	return(-1);
    }

    xmlFree(content);
    return(0);
}
