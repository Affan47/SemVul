parse_call_info_header( struct sip_msg *msg )
{
    struct call_info_body *callinfo_b, *old_callinfo_b=NULL;
    struct to_body *call_info_b;
    struct hdr_field *call_info;
    void **parsed;
    char *tmp, *end, *start;
    unsigned int len;

    if ( !msg->call_info &&
	 (parse_headers(msg, HDR_CALL_INFO_F,0)==-1 || !msg->call_info)) {
	return -1;
    }

    call_info=msg->call_info;


    if (call_info->parsed)
	return 0;

    parsed = &(call_info->parsed);

    while(*parsed == NULL)
{

    len = call_info->body.len+1;
    start = call_info->body.s;
    end = start + len;
    LM_DBG("parsing the whole body [%.*s]\n", len, call_info->body.s);

    for( tmp=call_info->body.s; tmp<=end; tmp++) {
        if (*tmp == ',' || tmp==end) {
	    LM_DBG("[%.*s]\n",tmp-start,start);

	    callinfo_b = pkg_malloc(sizeof(struct call_info_body));
	    if (callinfo_b == NULL) {
		LM_ERR("out of pkg_memory\n");
		goto error;
	    }
	    memset(callinfo_b, 0, sizeof(struct call_info_body));


	    call_info_b = &(callinfo_b->call_info_body);
	    parse_to(start, tmp, call_info_b);
	    if (call_info_b->error == PARSE_ERROR) {
		LM_ERR("bad Call-Info header\n");
		pkg_free(call_info_b);
		set_err_info(OSER_EC_PARSER, OSER_EL_MEDIUM,
		    "error parsing Call-Info header");
		set_err_reply(400, "bad header");
		goto error;
	    }


	    if (*parsed == NULL)
	    	*parsed = callinfo_b;
	    else
		old_callinfo_b->next = callinfo_b;

	    old_callinfo_b = callinfo_b;

	    start = tmp + 1;
	}
    }
    call_info = call_info->sibling;
    LM_DBG("done ... next call_info [%p]\n", call_info);
    if (call_info == NULL) {
	break;
    }
    parsed = &(call_info->parsed);
}

    return 0;

error:
    return -1;
}
