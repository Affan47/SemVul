xmlSecQName2IntegerGetIntegerFromString(xmlSecQName2IntegerInfoConstPtr info,
                                        xmlNodePtr node, const xmlChar* qname,
                                        int* intValue) {
    const xmlChar* qnameLocalPart = NULL;
    xmlChar* qnamePrefix = NULL;
    const xmlChar* qnameHref;
    xmlNsPtr ns;
    int ret;

    xmlSecAssert2(info != NULL, -1);
    xmlSecAssert2(node != NULL, -1);
    xmlSecAssert2(qname != NULL, -1);
    xmlSecAssert2(intValue != NULL, -1);

    qnameLocalPart = xmlStrchr(qname, ':');
    if(qnameLocalPart != NULL) {
        qnamePrefix = xmlStrndup(qname, qnameLocalPart - qname);
        if(qnamePrefix == NULL) {
            xmlSecError(XMLSEC_ERRORS_HERE,
                        NULL,
                        "xmlStrndup",
                        XMLSEC_ERRORS_R_MALLOC_FAILED,
                        "node=%s,value=%s",
                        xmlSecErrorsSafeString(node->name),
                        xmlSecErrorsSafeString(qname));
            return(-1);
        }
        qnameLocalPart++;
    } else {
        qnamePrefix = NULL;
        qnameLocalPart = qname;
    }


    ns = xmlSearchNs(node->doc, node, qnamePrefix);
    if((ns == NULL) && (qnamePrefix != NULL)) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSearchNs",
                    XMLSEC_ERRORS_R_XML_FAILED,
                    "node=%s,qnamePrefix=%s",
                    xmlSecErrorsSafeString(node->name),
                    xmlSecErrorsSafeString(qnamePrefix));
        if(qnamePrefix != NULL) {
            xmlFree(qnamePrefix);
        }
        return(-1);
    }
    qnameHref = (ns != NULL) ? ns->href : BAD_CAST NULL;


    ret = xmlSecQName2IntegerGetInteger(info, qnameHref, qnameLocalPart, intValue);
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecQName2IntegerGetInteger",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    "node=%s,qnameLocalPart=%s,qnameHref=%s",
                    xmlSecErrorsSafeString(node->name),
                    xmlSecErrorsSafeString(qnameLocalPart),
                    xmlSecErrorsSafeString(qnameHref));
        if(qnamePrefix != NULL) {
            xmlFree(qnamePrefix);
        }
        return(-1);
    }

    if(qnamePrefix != NULL) {
        xmlFree(qnamePrefix);
    }
    return(0);
}
