tds_gss_handle_next(TDSSOCKET * tds, struct tds_authentication * auth, size_t len)
{
	int res;
	gss_buffer_desc recv_tok;

	if (((struct tds_gss_auth *) auth)->last_stat != GSS_S_CONTINUE_NEEDED)
		return TDS_FAIL;

	if (auth->packet) {
		OM_uint32 min_stat;
		gss_buffer_desc send_tok;

		send_tok.value = (void *) auth->packet;
		send_tok.length = auth->packet_len;
		gss_release_buffer(&min_stat, &send_tok);
		auth->packet = NULL;
	}

	recv_tok.length = len;
	recv_tok.value = (char* ) malloc(len);
	if (!recv_tok.value)
		return TDS_FAIL;
	tds_get_n(tds, recv_tok.value, len);

	res = tds_gss_continue(tds, (struct tds_gss_auth *) auth, &recv_tok);
	free(recv_tok.value);
	if (res != TDS_SUCCEED)
		return TDS_FAIL;

	if (auth->packet_len) {
		tds->out_flag = TDS7_AUTH;
		tds_put_n(tds, auth->packet, auth->packet_len);
		return tds_flush_packet(tds);
	}
	return TDS_SUCCEED;
}
