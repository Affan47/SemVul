render_xml(isc_uint32_t flags, const char *url, isc_httpdurl_t *urlinfo,
	   const char *querystring, const char *headers, void *arg,
	   unsigned int *retcode, const char **retmsg,
	   const char **mimetype, isc_buffer_t *b,
	   isc_httpdfree_t **freecb, void **freecb_args)
{
	unsigned char *msg = NULL;
	int msglen;
	ns_server_t *server = arg;
	isc_result_t result;

	UNUSED(url);
	UNUSED(urlinfo);
	UNUSED(headers);
	UNUSED(querystring);

	result = generatexml(server, flags, &msglen, &msg);

	if (result == ISC_R_SUCCESS) {
		*retcode = 200;
		*retmsg = "OK";
		*mimetype = "text/xml";
		isc_buffer_reinit(b, msg, msglen);
		isc_buffer_add(b, msglen);
		*freecb = wrap_xmlfree;
		*freecb_args = NULL;
	} else
		isc_log_write(ns_g_lctx, NS_LOGCATEGORY_GENERAL,
			      NS_LOGMODULE_SERVER, ISC_LOG_ERROR,
			      "failed at rendering XML()");

	return (result);
}
