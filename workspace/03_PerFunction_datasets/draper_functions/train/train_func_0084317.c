xmlSecQName2BitMaskGetStringFromBitMask(xmlSecQName2BitMaskInfoConstPtr info,
					xmlNodePtr node, xmlSecBitMask mask) {
    xmlSecQName2BitMaskInfoConstPtr qnameInfo;

    xmlSecAssert2(info != NULL, NULL);
    xmlSecAssert2(node != NULL, NULL);

    qnameInfo = xmlSecQName2BitMaskGetInfo(info, mask);
    if(qnameInfo == NULL) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    "xmlSecQName2BitMaskGetInfo",
	    	    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    "node=%s,mask=%d",
		    xmlSecErrorsSafeString(node->name),
                    mask);
        return(NULL);
    }

    return(xmlSecGetQName(node, qnameInfo->qnameHref, qnameInfo->qnameLocalPart));
}
