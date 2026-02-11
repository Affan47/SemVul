cs42l52_beep_work(struct work_struct *work)
{
	struct cs42l52_private *cs42l52 =
		container_of(work, struct cs42l52_private, beep_work);
	struct snd_soc_codec *codec = cs42l52->codec;
	struct snd_soc_dapm_context *dapm = snd_soc_codec_get_dapm(codec);
	int i;
	int val = 0;
	int best = 0;

	if (cs42l52->beep_rate) {
		for (i = 0; i < ARRAY_SIZE(beep_rates); i++) {
			if (abs(cs42l52->beep_rate - beep_rates[i]) <
			    abs(cs42l52->beep_rate - beep_rates[best]))
				best = i;
		}

		dev_dbg(codec->dev, "Set beep rate %dHz for requested %dHz\n",
			beep_rates[best], cs42l52->beep_rate);

		val = (best << CS42L52_BEEP_RATE_SHIFT);

		snd_soc_dapm_enable_pin(dapm, "Beep");
	} else {
		dev_dbg(codec->dev, "Disabling beep\n");
		snd_soc_dapm_disable_pin(dapm, "Beep");
	}

	snd_soc_update_bits(codec, CS42L52_BEEP_FREQ,
			    CS42L52_BEEP_RATE_MASK, val);

	snd_soc_dapm_sync(dapm);
}
