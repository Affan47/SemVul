http_url_handler_404(struct http_connection *hc, int cbtype, void *arg) {
	int		err;

	Dprintf("%s: cbtype %d\n", __FUNCTION__, cbtype);


	if (cbtype == HCB_QUERY) {
		err=http_return_simple(hc,
				"404 Not found",
				"text/html",
				http_static_msg_404,
				strlen(http_static_msg_404));
		return 1;
	}


	http_request_end(hc);

	return 1;
}
