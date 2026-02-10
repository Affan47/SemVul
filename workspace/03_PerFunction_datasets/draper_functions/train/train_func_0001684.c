evhttp_send_reply_chunk_with_cb(struct evhttp_request *req, struct evbuffer *databuf,
    void (*cb)(struct evhttp_connection *, void *), void *arg)
{
	struct evhttp_connection *evcon = req->evcon;
	struct evbuffer *output;

	if (evcon == NULL)
		return;

	output = bufferevent_get_output(evcon->bufev);

	if (evbuffer_get_length(databuf) == 0)
		return;
	if (!evhttp_response_needs_body(req))
		return;
	if (req->chunked) {
		evbuffer_add_printf(output, "%x\r\n",
				    (unsigned)evbuffer_get_length(databuf));
	}
	evbuffer_add_buffer(output, databuf);
	if (req->chunked) {
		evbuffer_add(output, "\r\n", 2);
	}
	evhttp_write_buffer(evcon, cb, arg);
}
