httpMakeVaryMark(request_t * request, HttpReply * reply)
{
    String vary = StringNull, hdr;
    const char *pos = NULL;
    const char *item;
    const char *value;
    int ilen;
    String vstr = StringNull;

    stringClean(&vstr);
    hdr = httpHeaderGetList(&reply->header, HDR_VARY);
    if (strBuf(hdr))
	strListAdd(&vary, strBuf(hdr), ',');
    stringClean(&hdr);
#if X_ACCELERATOR_VARY
    hdr = httpHeaderGetList(&reply->header, HDR_X_ACCELERATOR_VARY);
    if (strBuf(hdr))
	strListAdd(&vary, strBuf(hdr), ',');
    stringClean(&hdr);
#endif
    while (strListGetItem(&vary, ',', &item, &ilen, &pos)) {
	char *name = xmalloc(ilen + 1);
	xstrncpy(name, item, ilen + 1);
	Tolower(name);
	if (strcmp(name, "accept-encoding") == 0) {
	    aclCheck_t checklist;
	    memset(&checklist, 0, sizeof(checklist));
	    checklist.request = request;
	    checklist.reply = reply;
	    if (Config.accessList.vary_encoding && aclCheckFast(Config.accessList.vary_encoding, &checklist)) {
		stringClean(&request->vary_encoding);
		request->vary_encoding = httpHeaderGetStrOrList(&request->header, HDR_ACCEPT_ENCODING);
		strCat(request->vary_encoding, "");
	    }
	}
	if (strcmp(name, "*") == 0) {

	    safe_free(name);
	    stringClean(&vary);
	    stringClean(&vstr);
	    break;
	}
	strListAdd(&vstr, name, ',');
	hdr = httpHeaderGetByName(&request->header, name);
	safe_free(name);
	value = strBuf(hdr);
	if (value) {
	    value = rfc1738_escape_part(value);
	    stringAppend(&vstr, "=\"", 2);
	    stringAppend(&vstr, value, strlen(value));
	    stringAppend(&vstr, "\"", 1);
	}
	stringClean(&hdr);
    }
    safe_free(request->vary_hdr);
    safe_free(request->vary_headers);
    if (strBuf(vary) && strBuf(vstr)) {
	request->vary_hdr = xstrdup(strBuf(vary));
	request->vary_headers = xstrdup(strBuf(vstr));
    }
    debug(11, 3) ("httpMakeVaryMark: %s\n", strBuf(vstr));
    stringClean(&vary);
    stringClean(&vstr);
    return request->vary_headers;
}
