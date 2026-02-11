_soup_get_xmlrpc_value_string(SoupMessage * msg,
					    SyncNetAction * sna)
{
    gchar *string = NULL;

    sna->error = NULL;

    if (!SOUP_STATUS_IS_SUCCESSFUL(msg->status_code)) {
	SNA_ERROR(1, "%s (error #%d)", msg->reason_phrase,
		  msg->status_code);
	goto bad;
    }

    if (!soup_xmlrpc_extract_method_response(msg->response_body->data,
					     msg->response_body->length,
					     NULL,
					     G_TYPE_STRING, &string)) {
	SNA_ERROR(2, "Could not parse XML-RPC response");
    }

  bad:
    return string;
}
