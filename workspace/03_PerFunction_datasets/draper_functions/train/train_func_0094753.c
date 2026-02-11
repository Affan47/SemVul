print_wowlan_handler(struct nl_msg *msg, void *arg)
{
	struct nlattr *attrs[NL80211_ATTR_MAX + 1];
	struct nlattr *trig[NUM_NL80211_WOWLAN_TRIG];
	struct genlmsghdr *gnlh = nlmsg_data(nlmsg_hdr(msg));
	struct nlattr *pattern;
	int rem_pattern;

	nla_parse(attrs, NL80211_ATTR_MAX, genlmsg_attrdata(gnlh, 0),
		  genlmsg_attrlen(gnlh, 0), NULL);

	if (!attrs[NL80211_ATTR_WOWLAN_TRIGGERS]) {
		printf("WoWLAN is disabled.\n");
		return NL_SKIP;
	}


	nla_parse(trig, MAX_NL80211_WOWLAN_TRIG,
		  nla_data(attrs[NL80211_ATTR_WOWLAN_TRIGGERS]),
		  nla_len(attrs[NL80211_ATTR_WOWLAN_TRIGGERS]),
		  NULL);

	printf("WoWLAN is enabled:\n");
	if (trig[NL80211_WOWLAN_TRIG_ANY])
		printf(" * wake up on special any trigger\n");
	if (trig[NL80211_WOWLAN_TRIG_DISCONNECT])
		printf(" * wake up on disconnect\n");
	if (trig[NL80211_WOWLAN_TRIG_MAGIC_PKT])
		printf(" * wake up on magic packet\n");
	if (trig[NL80211_WOWLAN_TRIG_GTK_REKEY_FAILURE])
		printf(" * wake up on GTK rekeying failure\n");
	if (trig[NL80211_WOWLAN_TRIG_EAP_IDENT_REQUEST])
		printf(" * wake up on EAP identity request\n");
	if (trig[NL80211_WOWLAN_TRIG_4WAY_HANDSHAKE])
		printf(" * wake up on 4-way handshake\n");
	if (trig[NL80211_WOWLAN_TRIG_RFKILL_RELEASE])
		printf(" * wake up on RF-kill release\n");
	if (trig[NL80211_WOWLAN_TRIG_PKT_PATTERN]) {
		nla_for_each_nested(pattern,
				    trig[NL80211_WOWLAN_TRIG_PKT_PATTERN],
				    rem_pattern) {
			struct nlattr *patattr[NUM_NL80211_WOWLAN_PKTPAT];
			int i, patlen, masklen;
			uint8_t *mask, *pat;
			nla_parse(patattr, MAX_NL80211_WOWLAN_PKTPAT,
				  nla_data(pattern), nla_len(pattern),
				  NULL);
			if (!patattr[NL80211_WOWLAN_PKTPAT_MASK] ||
			    !patattr[NL80211_WOWLAN_PKTPAT_PATTERN]) {
				printf(" * (invalid pattern specification)\n");
				continue;
			}
			masklen = nla_len(patattr[NL80211_WOWLAN_PKTPAT_MASK]);
			patlen = nla_len(patattr[NL80211_WOWLAN_PKTPAT_PATTERN]);
			if (DIV_ROUND_UP(patlen, 8) != masklen) {
				printf(" * (invalid pattern specification)\n");
				continue;
			}
			printf(" * wake up on pattern: ");
			pat = nla_data(patattr[NL80211_WOWLAN_PKTPAT_PATTERN]);
			mask = nla_data(patattr[NL80211_WOWLAN_PKTPAT_MASK]);
			for (i = 0; i < patlen; i++) {
				if (mask[i / 8] & (1 << (i % 8)))
					printf("%.2x", pat[i]);
				else
					printf("--");
				if (i != patlen - 1)
					printf(":");
			}
			printf("\n");
		}
	}

	return NL_SKIP;
}
