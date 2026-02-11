vmsg_build_oob_reply_ind(const struct guid *muid, uint8 hits, bool secure)
{
	uint32 msgsize;
	uint32 paysize = sizeof(uint8) + sizeof(uint8);
	char *payload;

	g_assert(muid);

	msgsize = vmsg_fill_header(v_tmp_header, paysize, sizeof v_tmp);
	gnutella_header_set_muid(v_tmp_header, muid);
	payload = vmsg_fill_type(v_tmp_data, T_LIME, 12, secure ? 3 : 2);

	payload[0] = hits;
	payload[1] = GNET_PROPERTY(is_udp_firewalled) ? 0x0 : 0x1;


	return gmsg_to_ctrl_pmsg(v_tmp, msgsize);
}
