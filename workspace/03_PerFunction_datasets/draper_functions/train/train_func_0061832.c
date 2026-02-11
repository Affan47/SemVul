max98090_seq_notifier(struct snd_soc_dapm_context *dapm,
	enum snd_soc_dapm_type event, int subseq)
{
	struct snd_soc_codec *codec = snd_soc_dapm_to_codec(dapm);
	struct max98090_priv *max98090 = snd_soc_codec_get_drvdata(codec);

	if (max98090->shdn_pending) {
		snd_soc_update_bits(codec, M98090_REG_DEVICE_SHUTDOWN,
				M98090_SHDNN_MASK, 0);
		msleep(40);
		snd_soc_update_bits(codec, M98090_REG_DEVICE_SHUTDOWN,
				M98090_SHDNN_MASK, M98090_SHDNN_MASK);
		max98090->shdn_pending = false;
	}
}
