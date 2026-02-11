ieee80211_is_empty_essid(const char *essid, int essid_len)
{

	if (essid_len == 1 && essid[0] == ' ')
		return 1;


	while (essid_len) {
		essid_len--;
		if (essid[essid_len] != '\0')
			return 0;
	}

	return 1;
}
