pppoe_send_PADO(struct pppoe_serv_t *serv, const uint8_t *addr, const struct pppoe_tag *host_uniq, const struct pppoe_tag *relay_sid, const struct pppoe_tag *service_name)
{
	uint8_t pack[ETHER_MAX_LEN];
	uint8_t cookie[COOKIE_LENGTH];

	setup_header(pack, serv->hwaddr, addr, CODE_PADO, 0);

	add_tag(pack, TAG_AC_NAME, (uint8_t *)conf_ac_name, strlen(conf_ac_name));
	if (conf_service_name)
		add_tag(pack, TAG_SERVICE_NAME, (uint8_t *)conf_service_name, strlen(conf_service_name));

	if (service_name)
		add_tag2(pack, service_name);

	generate_cookie(serv, addr, cookie, host_uniq, relay_sid);

	add_tag(pack, TAG_AC_COOKIE, cookie, COOKIE_LENGTH);

	if (host_uniq)
		add_tag2(pack, host_uniq);

	if (relay_sid)
		add_tag2(pack, relay_sid);

	if (conf_verbose) {
		log_info2("send ");
		print_packet(pack);
	}

	__sync_add_and_fetch(&stat_PADO_sent, 1);
	pppoe_send(serv->hnd.fd, pack);
}
