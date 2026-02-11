dom_check_qname(char *qname, char **localname, char **prefix, int uri_len, int name_len) {
	if (name_len == 0) {
		return NAMESPACE_ERR;
	}

	*localname = (char *)xmlSplitQName2((xmlChar *)qname, (xmlChar **) prefix);
	if (*localname == NULL) {
		*localname = (char *)xmlStrdup((xmlChar *)qname);
		if (*prefix == NULL && uri_len == 0) {
			return 0;
		}
	}


	if (xmlValidateQName((xmlChar *) qname, 0) != 0) {
		return NAMESPACE_ERR;
	}


	if (*prefix != NULL && uri_len == 0) {
		return NAMESPACE_ERR;
	}

	return 0;
}
