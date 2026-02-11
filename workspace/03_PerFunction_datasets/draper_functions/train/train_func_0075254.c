wlc_phy_chanspec_band_validch(struct brcms_phy_pub *ppi, uint band,
			      struct brcms_chanvec *channels)
{
	struct brcms_phy *pi = container_of(ppi, struct brcms_phy, pubpi_ro);
	uint i;
	uint channel;

	memset(channels, 0, sizeof(struct brcms_chanvec));

	for (i = 0; i < ARRAY_SIZE(chan_info_all); i++) {
		channel = chan_info_all[i].chan;

		if ((pi->a_band_high_disable) && (channel >= FIRST_REF5_CHANNUM)
		    && (channel <= LAST_REF5_CHANNUM))
			continue;

		if ((band == BRCM_BAND_2G && channel <= CH_MAX_2G_CHANNEL) ||
		    (band == BRCM_BAND_5G && channel > CH_MAX_2G_CHANNEL))
			setbit(channels->vec, channel);
	}
}
