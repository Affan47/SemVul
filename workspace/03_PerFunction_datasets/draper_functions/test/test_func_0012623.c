xmlSecAddChild(xmlNodePtr parent, const xmlChar *name, const xmlChar *ns) {
    xmlNodePtr cur;
    xmlNodePtr text;

    xmlSecAssert2(parent != NULL, NULL);
    xmlSecAssert2(name != NULL, NULL);

    if(parent->children == NULL) {

	text = xmlNewText(xmlSecStringCR);
        if(text == NULL) {
	    xmlSecError(XMLSEC_ERRORS_HERE,
			NULL,
			"xmlNewText",
			XMLSEC_ERRORS_R_XML_FAILED,
			XMLSEC_ERRORS_NO_MESSAGE);
	    return(NULL);
	}
	xmlAddChild(parent, text);
    }

    cur = xmlNewChild(parent, NULL, name, NULL);
    if(cur == NULL) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    "xmlNewChild",
		    XMLSEC_ERRORS_R_XML_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	return(NULL);
    }


    if(ns != NULL) {
	xmlNsPtr nsPtr;


	nsPtr = xmlSearchNsByHref(cur->doc, cur, ns);
	if((nsPtr == NULL) || (xmlSearchNs(cur->doc, cur, nsPtr->prefix) != nsPtr)) {
	    nsPtr = xmlNewNs(cur, ns, NULL);
	}
	xmlSetNs(cur, nsPtr);
    }


    text = xmlNewText(xmlSecStringCR);
    if(text == NULL) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    "xmlNewText",
		    XMLSEC_ERRORS_R_XML_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	return(NULL);
    }
    xmlAddChild(parent, text);

    return(cur);
}
