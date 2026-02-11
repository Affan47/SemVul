ipset_parse_tcp_udp_port(struct ipset_session *session,
			 enum ipset_opt opt, const char *str)
{
	struct ipset_data *data;
	int err = 0;
	uint8_t	p = 0;

	err = ipset_parse_proto_port(session, opt, str);

	if (!err) {
		data = ipset_session_data(session);

		p = *(const uint8_t *) ipset_data_get(data, IPSET_OPT_PROTO);
		if (p != IPPROTO_TCP && p != IPPROTO_UDP) {
			syntax_err("Only protocols TCP and UDP are valid");
			err = -1 ;
		} else {

			ipset_data_flags_unset(data, IPSET_FLAG(IPSET_OPT_PROTO));
		}
	}
	return err;
}
