pppcp_send_configure_request(struct pppcp_data *pppcp)
{
	struct pppcp_packet *packet;
	struct pppcp_timer_data *timer_data = &pppcp->config_timer_data;

	pppcp_trace(pppcp);

	packet = pppcp_packet_new(pppcp, PPPCP_CODE_TYPE_CONFIGURE_REQUEST,
					pppcp->local_options_len);
	memcpy(packet->data, pppcp->local_options, pppcp->local_options_len);


	if (is_first_request(timer_data))
		pppcp->config_identifier =
			new_identity(pppcp, pppcp->config_identifier);
	packet->identifier = pppcp->config_identifier;

	ppp_transmit(pppcp->ppp, pppcp_to_ppp_packet(packet),
			ntohs(packet->length));

	pppcp_packet_free(packet);


	timer_data->restart_counter--;
	pppcp_start_timer(timer_data);
}
