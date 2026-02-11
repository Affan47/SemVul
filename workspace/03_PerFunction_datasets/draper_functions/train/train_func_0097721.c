mac80211_setchannel_cache(const char *interface, void *handle,
							  void *family, int channel,
							  unsigned int chmode, char *errstr) {
#ifndef HAVE_LINUX_NETLINK
	snprintf(errstr, STATUS_MAX, "Kismet was not compiled with netlink/mac80211 "
			 "support, check the output of ./configure for why");

	return -22;
#else
	struct nl_sock *nl_handle = (struct nl_sock *) handle;
	struct genl_family *nl80211 = (struct genl_family *) family;
	struct nl_msg *msg;
	int ret = 0;

	int chanmode[] = {
		NL80211_CHAN_NO_HT, NL80211_CHAN_HT20,
		NL80211_CHAN_HT40PLUS, NL80211_CHAN_HT40MINUS
	};

	if (chmode > 4) {
		snprintf(errstr, STATUS_MAX, "Invalid channel mode\n");
		return -1;
	}

	if ((msg = nlmsg_alloc()) == NULL) {
		snprintf(errstr, STATUS_MAX, "mac80211_setchannel() failed to allocate "
				 "message");
		return -1;
	}

	genlmsg_put(msg, 0, 0, genl_family_get_id(nl80211), 0, 0,
				NL80211_CMD_SET_WIPHY, 0);
	NLA_PUT_U32(msg, NL80211_ATTR_IFINDEX, if_nametoindex(interface));
	NLA_PUT_U32(msg, NL80211_ATTR_WIPHY_FREQ, ChanToFreq(channel));
	NLA_PUT_U32(msg, NL80211_ATTR_WIPHY_CHANNEL_TYPE, chanmode[chmode]);

	if ((ret = nl_send_auto_complete(nl_handle, msg)) >= 0) {
		if ((ret = nl_wait_for_ack(nl_handle)) < 0)
			goto nla_put_failure;
	}

	nlmsg_free(msg);

	return 0;

nla_put_failure:
	snprintf(errstr, STATUS_MAX, "mac80211_setchannel() could not set channel "
			 "%d/%d on interface '%s' err %d", channel, ChanToFreq(channel),
			 interface, ret);
	nlmsg_free(msg);
	return ret;
#endif
}
