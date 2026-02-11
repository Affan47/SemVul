ast_channel_queue_connected_line_update(struct ast_channel *chan, const struct ast_party_connected_line *connected, const struct ast_set_party_connected_line *update)
{
	unsigned char data[1024];
	size_t datalen;

	datalen = ast_connected_line_build_data(data, sizeof(data), connected, update);
	if (datalen == (size_t) -1) {
		return;
	}

	ast_queue_control_data(chan, AST_CONTROL_CONNECTED_LINE, data, datalen);
}
