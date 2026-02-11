rt286_set_bias_level(struct snd_soc_codec *codec,
				 enum snd_soc_bias_level level)
{
	switch (level) {
	case SND_SOC_BIAS_PREPARE:
		if (SND_SOC_BIAS_STANDBY == snd_soc_codec_get_bias_level(codec)) {
			snd_soc_write(codec,
				RT286_SET_AUDIO_POWER, AC_PWRST_D0);
			snd_soc_update_bits(codec,
				RT286_DC_GAIN, 0x200, 0x200);
		}
		break;

	case SND_SOC_BIAS_ON:
		mdelay(10);
		snd_soc_update_bits(codec,
			RT286_CBJ_CTRL1, 0x0400, 0x0400);
		snd_soc_update_bits(codec,
			RT286_DC_GAIN, 0x200, 0x0);

		break;

	case SND_SOC_BIAS_STANDBY:
		snd_soc_write(codec,
			RT286_SET_AUDIO_POWER, AC_PWRST_D3);
		snd_soc_update_bits(codec,
			RT286_CBJ_CTRL1, 0x0400, 0x0000);
		break;

	default:
		break;
	}

	return 0;
}
