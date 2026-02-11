report_cal_multiget(struct transaction_t *txn,
			       xmlNodePtr inroot, struct propfind_ctx *fctx)
{
    int r, ret = 0;
    struct request_target_t tgt;
    struct mailbox *mailbox = NULL;
    xmlNodePtr node;
    struct buf uri = BUF_INITIALIZER;

    memset(&tgt, 0, sizeof(struct request_target_t));
    tgt.namespace = URL_NS_CALENDAR;


    for (node = inroot->children; node; node = node->next) {
	if ((node->type == XML_ELEMENT_NODE) &&
	    !xmlStrcmp(node->name, BAD_CAST "href")) {
	    xmlChar *href = xmlNodeListGetString(inroot->doc, node->children, 1);
	    int len = xmlStrlen(href);
	    struct caldav_data *cdata;

	    buf_ensure(&uri, len);
	    xmlURIUnescapeString((const char *) href, len, uri.s);
	    xmlFree(href);


	    if ((r = caldav_parse_path(uri.s, &tgt, &fctx->err->desc))) {
		ret = r;
		goto done;
	    }

	    fctx->req_tgt = &tgt;


	    if (!mailbox || strcmp(mailbox->name, tgt.mboxname)) {
		if (mailbox) mailbox_unlock_index(mailbox, NULL);


		if ((r = http_mailbox_open(tgt.mboxname, &mailbox, LOCK_SHARED))) {
		    syslog(LOG_ERR, "http_mailbox_open(%s) failed: %s",
			   tgt.mboxname, error_message(r));
		    txn->error.desc = error_message(r);
		    ret = HTTP_SERVER_ERROR;
		    goto done;
		}

		fctx->mailbox = mailbox;
	    }


	    caldav_lookup_resource(auth_caldavdb,
				   tgt.mboxname, tgt.resource, 0, &cdata);
	    cdata->dav.resource = tgt.resource;


	    propfind_by_resource(fctx, cdata);
	}
    }

  done:
    if (mailbox) mailbox_unlock_index(mailbox, NULL);
    buf_free(&uri);

    return ret;
}
