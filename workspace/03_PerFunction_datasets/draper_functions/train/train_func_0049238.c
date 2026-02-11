tipc_print(netdissect_options *ndo, const u_char *bp, u_int length _U_,
    u_int caplen _U_)
{
	const struct tipc_pkthdr *ap;
	u_int32_t w0;
	u_int user;

	ap = (struct tipc_pkthdr *)bp;
	ND_TCHECK(ap->w0);
	w0 = EXTRACT_32BITS(&ap->w0);
	user = TIPC_USER(w0);

	switch (user)
	{
		case TIPC_USER_LOW_IMPORTANCE:
		case TIPC_USER_MEDIUM_IMPORTANCE:
		case TIPC_USER_HIGH_IMPORTANCE:
		case TIPC_USER_CRITICAL_IMPORTANCE:
		case TIPC_USER_NAME_DISTRIBUTOR:
		case TIPC_USER_CONN_MANAGER:
			print_payload(ndo, (struct payload_tipc_pkthdr *)bp);
			break;

		case TIPC_USER_LINK_CONFIG:
			print_link_conf(ndo, (struct link_conf_tipc_pkthdr *)bp);
			break;

		case TIPC_USER_BCAST_PROTOCOL:
		case TIPC_USER_MSG_BUNDLER:
		case TIPC_USER_LINK_PROTOCOL:
		case TIPC_USER_CHANGEOVER_PROTOCOL:
		case TIPC_USER_MSG_FRAGMENTER:
			print_internal(ndo, (struct internal_tipc_pkthdr *)bp);
			break;

	}
	return;

trunc:
	ND_PRINT((ndo, "[|TIPC]"));
}
