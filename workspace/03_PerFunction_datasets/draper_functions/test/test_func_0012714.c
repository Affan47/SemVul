MXHeloOK(char const *sockname,
	 char *msg,
	 char const *ip,
	 char const *name,
	 char const *helo,
	 unsigned int port,
	 char const *myip,
	 unsigned int daemon_port)
{
    char cmd[SMALLBUF];
    char ans[SMALLBUF];

    char port_string[65];
    char daemon_port_string[65];

    snprintf(port_string, sizeof(port_string), "%u", port);
    snprintf(daemon_port_string, sizeof(daemon_port_string), "%u", daemon_port);

    *msg = 0;

    if (!ip || !*ip) {
	ip = "UNKNOWN";
    }
    if (!name || !*name) {
	name = ip;
    }
    if (!helo) {
	helo = "UNKNOWN";
    }

    if (!myip || !*myip) {
	myip = "UNKNOWN";
    }

    if (percent_encode_command(1, cmd, sizeof(cmd), "helook", ip, name, helo, port_string, myip, daemon_port_string, NULL) < 0) {
	return MD_TEMPFAIL;
    }
    if (MXCommand(sockname, cmd, ans, SMALLBUF-1) < 0) return MD_TEMPFAIL;
    return munch_mx_return(ans, msg);
}
