libipw_freq_to_channel(struct libipw_device * ieee, u32 freq)
{
	int i;


	if (ieee->geo.bg_channels == 0 && ieee->geo.a_channels == 0)
		return 0;

	freq /= 100000;

	if (ieee->freq_band & LIBIPW_24GHZ_BAND)
		for (i = 0; i < ieee->geo.bg_channels; i++)
			if (ieee->geo.bg[i].freq == freq)
				return ieee->geo.bg[i].channel;

	if (ieee->freq_band & LIBIPW_52GHZ_BAND)
		for (i = 0; i < ieee->geo.a_channels; i++)
			if (ieee->geo.a[i].freq == freq)
				return ieee->geo.a[i].channel;

	return 0;
}
