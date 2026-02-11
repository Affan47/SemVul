wm8994_set_tristate(struct snd_soc_dai *codec_dai, int tristate)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	int reg, val, mask;

	switch (codec_dai->id) {
	case 1:
		reg = WM8994_AIF1_MASTER_SLAVE;
		mask = WM8994_AIF1_TRI;
		break;
	case 2:
		reg = WM8994_AIF2_MASTER_SLAVE;
		mask = WM8994_AIF2_TRI;
		break;
	default:
		return -EINVAL;
	}

	if (tristate)
		val = mask;
	else
		val = 0;

	return snd_soc_update_bits(codec, reg, mask, val);
}
