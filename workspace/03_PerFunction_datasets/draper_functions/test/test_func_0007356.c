enable_power_depop(struct snd_soc_codec *codec)
{
	struct alc5623_priv *alc5623 = snd_soc_codec_get_drvdata(codec);

	snd_soc_update_bits(codec, ALC5623_PWR_MANAG_ADD1,
				ALC5623_PWR_ADD1_SOFTGEN_EN,
				ALC5623_PWR_ADD1_SOFTGEN_EN);

	snd_soc_write(codec, ALC5623_PWR_MANAG_ADD3, ALC5623_ADD3_POWER_EN);

	snd_soc_update_bits(codec, ALC5623_MISC_CTRL,
				ALC5623_MISC_HP_DEPOP_MODE2_EN,
				ALC5623_MISC_HP_DEPOP_MODE2_EN);

	msleep(500);

	snd_soc_write(codec, ALC5623_PWR_MANAG_ADD2, ALC5623_ADD2_POWER_EN);


	if (alc5623->id == 0x22)
		snd_soc_write(codec, ALC5623_PWR_MANAG_ADD1,
			ALC5623_ADD1_POWER_EN_5622);
	else
		snd_soc_write(codec, ALC5623_PWR_MANAG_ADD1,
			ALC5623_ADD1_POWER_EN);


	snd_soc_update_bits(codec, ALC5623_MISC_CTRL,
				ALC5623_MISC_HP_DEPOP_MODE2_EN,
				0);

}
