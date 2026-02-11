ak4613_set_bias_level(struct snd_soc_codec *codec,
				 enum snd_soc_bias_level level)
{
	u8 mgmt1 = 0;

	switch (level) {
	case SND_SOC_BIAS_ON:
		mgmt1 |= RSTN;

	case SND_SOC_BIAS_PREPARE:
		mgmt1 |= PMADC | PMDAC;

	case SND_SOC_BIAS_STANDBY:
		mgmt1 |= PMVR;

	case SND_SOC_BIAS_OFF:
	default:
		break;
	}

	snd_soc_write(codec, PW_MGMT1, mgmt1);

	return 0;
}
