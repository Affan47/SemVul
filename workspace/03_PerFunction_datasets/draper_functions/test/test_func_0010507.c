ws_add_data(struct http_client *c) {

	enum ws_state state;

	state = ws_parse_data(c->buffer, c->sz, &c->frame);

	if(state == WS_MSG_COMPLETE) {
		int ret = ws_execute(c, c->frame->payload, c->frame->payload_sz);


		http_client_remove_data(c, c->frame->total_sz);


		ws_msg_free(&c->frame);

		if(ret != 0) {

			return WS_ERROR;
		}
	}
	return state;
}
