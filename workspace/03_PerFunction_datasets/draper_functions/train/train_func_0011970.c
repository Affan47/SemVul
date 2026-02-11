onscrd_mixervol(struct mame_bitmap *bitmap,int increment,int arg)
{
	static void *driver = 0;
	char buf[40];
	int volume,ch;
	int doallchannels = 0;
	int proportional = 0;


	if (code_pressed(KEYCODE_LSHIFT) || code_pressed(KEYCODE_RSHIFT))
		doallchannels = 1;
	if (!code_pressed(KEYCODE_LCONTROL) && !code_pressed(KEYCODE_RCONTROL))
		increment *= 5;
	if (code_pressed(KEYCODE_LALT) || code_pressed(KEYCODE_RALT))
		proportional = 1;

	if (increment)
	{
		if (proportional)
		{
			static int old_vol[MIXER_MAX_CHANNELS];
			float ratio = 1.0;
			int overflow = 0;

			if (driver != Machine->drv)
			{
				driver = (void *)Machine->drv;
				for (ch = 0; ch < MIXER_MAX_CHANNELS; ch++)
					old_vol[ch] = mixer_get_mixing_level(ch);
			}

			volume = mixer_get_mixing_level(arg);
			if (old_vol[arg])
				ratio = (float)(volume + increment) / (float)old_vol[arg];

			for (ch = 0; ch < MIXER_MAX_CHANNELS; ch++)
			{
				if (mixer_get_name(ch) != 0)
				{
					volume = ratio * old_vol[ch];
					if (volume < 0 || volume > 100)
						overflow = 1;
				}
			}

			if (!overflow)
			{
				for (ch = 0; ch < MIXER_MAX_CHANNELS; ch++)
				{
					volume = ratio * old_vol[ch];
					mixer_set_mixing_level(ch,volume);
				}
			}
		}
		else
		{
			driver = 0;

			volume = mixer_get_mixing_level(arg);
			volume += increment;
			if (volume > 100) volume = 100;
			if (volume < 0) volume = 0;

			if (doallchannels)
			{
				for (ch = 0;ch < MIXER_MAX_CHANNELS;ch++)
					mixer_set_mixing_level(ch,volume);
			}
			else
				mixer_set_mixing_level(arg,volume);
		}
	}
	volume = mixer_get_mixing_level(arg);

	if (proportional)
		sprintf(buf,"%s %s %3d%%", ui_getstring (UI_allchannels), ui_getstring (UI_relative), volume);
	else if (doallchannels)
		sprintf(buf,"%s %s %3d%%", ui_getstring (UI_allchannels), ui_getstring (UI_volume), volume);
	else
		sprintf(buf,"%s %s %3d%%",mixer_get_name(arg), ui_getstring (UI_volume), volume);
	displayosd(bitmap,buf,volume,mixer_get_default_mixing_level(arg));
}
