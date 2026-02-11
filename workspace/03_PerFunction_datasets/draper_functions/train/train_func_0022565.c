gf_term_get_service_info(GF_Terminal *term, GF_ObjectManager *odm, NetInfoCommand *netinfo)
{
	GF_Err e;
	GF_NetworkCommand com;
	if (!term || !odm || !netinfo || !gf_term_check_odm(term, odm)) return GF_BAD_PARAM;
	memset(&com, 0, sizeof(GF_NetworkCommand));
	com.command_type = GF_NET_SERVICE_INFO;
	e = gf_term_service_command(odm->net_service, &com);
	memcpy(netinfo, &com.info, sizeof(NetInfoCommand));
	return e;
}
