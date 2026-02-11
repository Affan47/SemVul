max98090_set_tdm_slot(struct snd_soc_dai *codec_dai,
	unsigned int tx_mask, unsigned int rx_mask, int slots, int slot_width)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	struct max98090_priv *max98090 = snd_soc_codec_get_drvdata(codec);
	struct max98090_cdata *cdata;
	cdata = &max98090->dai[0];

	if (slots < 0 || slots > 4)
		return -EINVAL;

	max98090->tdm_slots = slots;
	max98090->tdm_width = slot_width;

	if (max98090->tdm_slots > 1) {

		snd_soc_write(codec, M98090_REG_TDM_FORMAT,
			0 << M98090_TDM_SLOTL_SHIFT |
			1 << M98090_TDM_SLOTR_SHIFT |
			0 << M98090_TDM_SLOTDLY_SHIFT);


		snd_soc_update_bits(codec, M98090_REG_TDM_CONTROL,
			M98090_TDM_MASK,
			M98090_TDM_MASK);
	}


	cdata->fmt = 0;
	max98090_dai_set_fmt(codec_dai, max98090->dai_fmt);

	return 0;
}
