wlc_phy_channel2freq(uint channel)
{
	uint i;

	for (i = 0; i < ARRAY_SIZE(chan_info_all); i++)
		if (chan_info_all[i].chan == channel)
			return chan_info_all[i].freq;
	return 0;
}
