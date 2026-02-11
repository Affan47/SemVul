wlc_phy_chanspec_bandrange_get(struct brcms_phy *pi, u16 chanspec)
{
	int range = -1;
	uint channel = CHSPEC_CHANNEL(chanspec);
	uint freq = wlc_phy_channel2freq(channel);

	if (ISNPHY(pi))
		range = wlc_phy_get_chan_freq_range_nphy(pi, channel);
	else if (ISLCNPHY(pi))
		range = wlc_phy_chanspec_freq2bandrange_lpssn(freq);

	return range;
}
