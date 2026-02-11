xmlSecKeyInfoNodeRead(xmlNodePtr keyInfoNode, xmlSecKeyPtr key, xmlSecKeyInfoCtxPtr keyInfoCtx) {
    const xmlChar* nodeName;
    const xmlChar* nodeNs;
    xmlSecKeyDataId dataId;
    xmlNodePtr cur;
    int ret;

    xmlSecAssert2(keyInfoNode != NULL, -1);
    xmlSecAssert2(key != NULL, -1);
    xmlSecAssert2(keyInfoCtx != NULL, -1);
    xmlSecAssert2(keyInfoCtx->mode == xmlSecKeyInfoModeRead, -1);

    for(cur = xmlSecGetNextElementNode(keyInfoNode->children);
	(cur != NULL) &&
	(((keyInfoCtx->flags & XMLSEC_KEYINFO_FLAGS_DONT_STOP_ON_KEY_FOUND) != 0) ||
	 (xmlSecKeyIsValid(key) == 0) ||
	 (xmlSecKeyMatch(key, NULL, &(keyInfoCtx->keyReq)) == 0));
	cur = xmlSecGetNextElementNode(cur->next)) {


	nodeName = cur->name;
	nodeNs = xmlSecGetNodeNsHref(cur);


	if(xmlSecPtrListGetSize(&(keyInfoCtx->enabledKeyData)) > 0) {
	    dataId = xmlSecKeyDataIdListFindByNode(&(keyInfoCtx->enabledKeyData),
			    nodeName, nodeNs, xmlSecKeyDataUsageKeyInfoNodeRead);
	} else {
    	    dataId = xmlSecKeyDataIdListFindByNode(xmlSecKeyDataIdsGet(),
			    nodeName, nodeNs, xmlSecKeyDataUsageKeyInfoNodeRead);
	}
	if(dataId != xmlSecKeyDataIdUnknown) {

	    ret = xmlSecKeyDataXmlRead(dataId, key, cur, keyInfoCtx);
	    if(ret < 0) {
		xmlSecError(XMLSEC_ERRORS_HERE,
			    xmlSecErrorsSafeString(xmlSecKeyDataKlassGetName(dataId)),
			    "xmlSecKeyDataXmlRead",
			    XMLSEC_ERRORS_R_XMLSEC_FAILED,
			    "node=%s",
			    xmlSecErrorsSafeString(xmlSecNodeGetName(cur)));
		return(-1);
	    }
	} else if((keyInfoCtx->flags & XMLSEC_KEYINFO_FLAGS_STOP_ON_UNKNOWN_CHILD) != 0) {


	    xmlSecError(XMLSEC_ERRORS_HERE,
			NULL,
			xmlSecErrorsSafeString(xmlSecNodeGetName(cur)),
			XMLSEC_ERRORS_R_INVALID_NODE,
			XMLSEC_ERRORS_NO_MESSAGE);
	    return(-1);
	}
    }

    return(0);
}
