get_if_type(int *argc, char ***argv, enum nl80211_iftype *type,
		       bool need_type)
{
	char *tpstr;

	if (*argc < 1 + !!need_type)
		return 1;

	if (need_type && strcmp((*argv)[0], "type"))
		return 1;

	tpstr = (*argv)[!!need_type];
	*argc -= 1 + !!need_type;
	*argv += 1 + !!need_type;

	if (strcmp(tpstr, "adhoc") == 0 ||
	    strcmp(tpstr, "ibss") == 0) {
		*type = NL80211_IFTYPE_ADHOC;
		return 0;
	} else if (strcmp(tpstr, "monitor") == 0) {
		*type = NL80211_IFTYPE_MONITOR;
		return 0;
	} else if (strcmp(tpstr, "master") == 0 ||
		   strcmp(tpstr, "ap") == 0) {
		*type = NL80211_IFTYPE_UNSPECIFIED;
		fprintf(stderr, "You need to run a management daemon, e.g. hostapd,\n");
		fprintf(stderr, "see http://wireless.kernel.org/en/users/Documentation/hostapd\n");
		fprintf(stderr, "for more information on how to do that.\n");
		return 2;
	} else if (strcmp(tpstr, "__ap") == 0) {
		*type = NL80211_IFTYPE_AP;
		return 0;
	} else if (strcmp(tpstr, "__ap_vlan") == 0) {
		*type = NL80211_IFTYPE_AP_VLAN;
		return 0;
	} else if (strcmp(tpstr, "wds") == 0) {
		*type = NL80211_IFTYPE_WDS;
		return 0;
	} else if (strcmp(tpstr, "managed") == 0 ||
		   strcmp(tpstr, "mgd") == 0 ||
		   strcmp(tpstr, "station") == 0) {
		*type = NL80211_IFTYPE_STATION;
		return 0;
	} else if (strcmp(tpstr, "mp") == 0 ||
		   strcmp(tpstr, "mesh") == 0) {
		*type = NL80211_IFTYPE_MESH_POINT;
		return 0;
	} else if (strcmp(tpstr, "__p2pcl") == 0) {
		*type = NL80211_IFTYPE_P2P_CLIENT;
		return 0;
	} else if (strcmp(tpstr, "__p2pgo") == 0) {
		*type = NL80211_IFTYPE_P2P_GO;
		return 0;
	}

	fprintf(stderr, "invalid interface type %s\n", tpstr);
	return 2;
}
