ipoe_rad_send_request(struct rad_plugin_t *rad, struct rad_packet_t *pack)
{
	struct ipoe_session *ses = container_of(rad, typeof(*ses), radius);

	if (!ses->relay_agent)
		return 0;

	return rad_packet_add_octets(pack, NULL, conf_attr_dhcp_opt82, ses->relay_agent->data, ses->relay_agent->len);
}
