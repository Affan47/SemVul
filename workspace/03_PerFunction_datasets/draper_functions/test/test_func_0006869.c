gom_mixer_c_c_v_fade_meta(enum gom_info_types std_verb, int c, int cc, int v, int locksensible)
{
	int volume, diff;
	unsigned long micro_seconds_to_sleep = 5000;
	int fade_up;

	int old_v = gom_driver_c_c_v (c, cc);
	v = gom_driver_c_c_v_range (v);

	if (old_v < 0)
	{
		gom_info(GOM_INFO_ERROR,
						 "Can't fade volume %d on channel %d(%s): not available.",
						 cc, c, gom_driver_C_name(c, 0));
	}
	else if (v < 0)
	{

	}
	else
	{

		if (locksensible && gom_mixer_c_l(c))
			gom_info(std_verb,
							 "Fading all volumes of channel %d(%s) from %i to %i in about %i seconds.",
							 c, gom_driver_c_name(c, 0),
							 gom_driver_c_c_v(c, cc), v, gom_mixer_fadival());
		else
			gom_info(std_verb,
							 "Fading volume %d of channel %d(%s) from %i to %i in about %i seconds.",
							 cc,
							 c, gom_driver_c_name(c, 0), gom_driver_c_c_v(c, cc), v, gom_mixer_fadival());


		fade_up = (gom_driver_c_c_v(c, cc) <= v);
		diff = (fade_up ? (v - gom_driver_c_c_v(c, cc)) : (gom_driver_c_c_v(c, cc)-v));
		micro_seconds_to_sleep = (1000000 * gom_mixer_fadival());

		micro_seconds_to_sleep = micro_seconds_to_sleep / (diff != 0 ? diff : 1);

		for (fade_up ? (volume = gom_driver_c_c_v(c, cc)+1) : (volume = gom_driver_c_c_v(c, cc)-1);
				 fade_up ? volume < v        : volume > v;
				 fade_up ? ++volume          : --volume)
		{
			if (locksensible)
				gom_mixer_c_c_v_set_l(std_verb+1, c, cc, volume);
			else
				gom_driver_c_c_v_set(std_verb+1, c, cc, volume);
			usleep(micro_seconds_to_sleep);
		}
		if (locksensible)
			gom_mixer_c_c_v_set_l(std_verb+1, c, cc, v);
		else
			gom_driver_c_c_v_set(std_verb+1, c, cc, v);
	}
}
