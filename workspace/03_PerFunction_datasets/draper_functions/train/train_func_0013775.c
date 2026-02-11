icq_send_status_descr(session_t *s, int msg_type, msg_params_t *msg_param) {
	string_t pkt;
	char *desc;

	if (!msg_param->u) {
		debug_warn("icq_send_status_descr(). Ignore request from %s\n", msg_param->uid);
		return;
	}
	debug_function("icq_send_status_descr() to %s\n", msg_param->uid);

	pkt = string_init(NULL);

	desc = xstrdup(s->descr);
	icq_pack_append_msg_header(pkt, msg_param);
	icq_pack_append_rendezvous(pkt, msg_param->version, msg_param->cookie, msg_type, MFLAG_AUTO, 0, 0);
	if (msg_param->version == 9)
		desc = ekg_locale_to_utf8(desc);
	else {

	}
	icq_pack_append_nullterm_msg(pkt, desc);
	xfree(desc);

	icq_makesnac(s, pkt, 0x04, 0x0b, NULL, NULL);
	icq_send_pkt(s, pkt);
}
