dhcp6opt_name(int type)
{
	static char genstr[sizeof("opt_65535") + 1];

	if (type > 65535)
		return "INVALID option";

	switch(type) {
	case DH6OPT_CLIENTID:
		return "client ID";
	case DH6OPT_SERVERID:
		return "server ID";
	case DH6OPT_IA_NA:
		return "IA_NA";
	case DH6OPT_IA_TA:
		return "IA_TA";
	case DH6OPT_IA_ADDR:
		return "IA_ADDR";
	case DH6OPT_ORO:
		return "option request";
	case DH6OPT_PREFERENCE:
		return "preference";
	case DH6OPT_ELAPSED_TIME:
		return "elapsed time";
	case DH6OPT_RELAY_MSG:
		return "relay message";
	case DH6OPT_AUTH:
		return "authentication";
	case DH6OPT_UNICAST:
		return "server unicast";
	case DH6OPT_STATUS_CODE:
		return "status code";
	case DH6OPT_RAPID_COMMIT:
		return "rapid commit";
	case DH6OPT_USER_CLASS:
		return "user class";
	case DH6OPT_VENDOR_CLASS:
		return "vendor class";
	case DH6OPT_VENDOR_OPTS:
		return "vendor-specific info";
	case DH6OPT_INTERFACE_ID:
		return "interface ID";
	case DH6OPT_RECONF_MSG:
		return "reconfigure message";
	case DH6OPT_RECONF_ACCEPT:
		return "reconfigure accept";
	case DH6OPT_SIP_SERVER_D:
		return "SIP servers domain";
	case DH6OPT_SIP_SERVER_A:
		return "SIP servers address";
	case DH6OPT_DNS:
		return "DNS";
	case DH6OPT_DNSNAME:
		return "DNS name";
	case DH6OPT_IA_PD:
		return "IA_PD";
	case DH6OPT_IA_PD_PREFIX:
		return "IA_PD prefix";
	case DH6OPT_NTP_SERVERS:
		return "NTP Server";
	case DH6OPT_LIFETIME:
		return "lifetime";
	case DH6OPT_NIS_SERVERS:
		return "NIS server";
	case DH6OPT_NISP_SERVERS:
		return "NIS+ server";
	case DH6OPT_NIS_NAME:
		return "NIS domain name";
	case DH6OPT_NISP_NAME:
		return "NIS+ domain name";
	case DH6OPT_BCMCS_SERVER_D:
		return "BCMCS domain name";
	case DH6OPT_BCMCS_SERVER_A:
		return "BCMCS server";
	case DH6OPT_GEOCONF_CIVIC:
		return "Geoconf Civic";
	case DH6OPT_REMOTE_ID:
		return "Remote ID";
	case DH6OPT_SUBSCRIBER_ID:
		return "Subscriber ID";
	case DH6OPT_CLIENT_FQDN:
		return "Client FQDN";
	default:
		snprintf(genstr, sizeof(genstr), "opt_%d", type);
		return(genstr);
	}
}
