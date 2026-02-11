__prepare_listen_events(struct nl80211_state *state)
{
	int mcid, ret;


	mcid = nl_get_multicast_id(state->nl_sock, "nl80211", "config");
	if (mcid < 0)
		return mcid;

	ret = nl_socket_add_membership(state->nl_sock, mcid);
	if (ret)
		return ret;


	mcid = nl_get_multicast_id(state->nl_sock, "nl80211", "scan");
	if (mcid >= 0) {
		ret = nl_socket_add_membership(state->nl_sock, mcid);
		if (ret)
			return ret;
	}


	mcid = nl_get_multicast_id(state->nl_sock, "nl80211", "regulatory");
	if (mcid >= 0) {
		ret = nl_socket_add_membership(state->nl_sock, mcid);
		if (ret)
			return ret;
	}


	mcid = nl_get_multicast_id(state->nl_sock, "nl80211", "mlme");
	if (mcid >= 0) {
		ret = nl_socket_add_membership(state->nl_sock, mcid);
		if (ret)
			return ret;
	}

	return 0;
}
