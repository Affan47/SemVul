conf_set_connect_aftype(void *data)
{
	char *aft = data;

	if(strcasecmp(aft, "ipv4") == 0)
		yy_server->aftype = AF_INET;
#ifdef RB_IPV6
	else if(strcasecmp(aft, "ipv6") == 0)
		yy_server->aftype = AF_INET6;
#endif
	else
		conf_report_error("connect::aftype '%s' is unknown.", aft);
}
