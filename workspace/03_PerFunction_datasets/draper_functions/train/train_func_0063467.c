tcp_peer_input_handler(ioa_socket_handle s, int event_type, ioa_net_data *in_buffer, void *arg, int can_resume)
{
	if (!(event_type & IOA_EV_READ) || !arg)
		return;

	UNUSED_ARG(s);
	UNUSED_ARG(can_resume);

	tcp_connection *tc = (tcp_connection*)arg;
	ts_ur_super_session *ss=NULL;
	allocation *a=(allocation*)tc->owner;
	if(a) {
		ss=(ts_ur_super_session*)a->owner;
	}

	if((tc->state != TC_STATE_READY) || !(tc->client_s)) {
		add_unsent_buffer(&(tc->ub_to_client), in_buffer->nbh);
		in_buffer->nbh = NULL;
		return;
	}

	ioa_network_buffer_handle nbh = in_buffer->nbh;
	in_buffer->nbh = NULL;

	u32bits bytes = (u32bits)ioa_network_buffer_get_size(nbh);

	int ret = send_data_from_ioa_socket_nbh(tc->client_s, NULL, nbh, TTL_IGNORE, TOS_IGNORE);
	if (ret < 0) {
		set_ioa_socket_tobeclosed(s);
	} else if(ss) {
		++(ss->sent_packets);
		ss->sent_bytes += bytes;
		turn_report_session_usage(ss);
	}
}
