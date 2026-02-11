realtime_update_peer(const char *peername, struct ast_sockaddr *sockaddr, time_t regtime)
{
	char port[10];
	char regseconds[20];
	const char *sysname = ast_config_AST_SYSTEM_NAME;
	char *syslabel = NULL;

	if (ast_strlen_zero(sysname))
		sysname = NULL;
	else if (ast_test_flag64(&globalflags, IAX_RTSAVE_SYSNAME))
		syslabel = "regserver";

	snprintf(regseconds, sizeof(regseconds), "%d", (int)regtime);
	snprintf(port, sizeof(port), "%d", ast_sockaddr_port(sockaddr));
	ast_update_realtime("iaxpeers", "name", peername,
		"ipaddr", ast_sockaddr_stringify_addr(sockaddr), "port", port,
		"regseconds", regseconds, syslabel, sysname, SENTINEL);
}
