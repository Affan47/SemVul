pm860x_pcm_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;
	unsigned char inf = 0, mask = 0;


	switch (params_width(params)) {
	case 16:
		inf &= ~PCM_INF2_18WL;
		break;
	case 18:
		inf |= PCM_INF2_18WL;
		break;
	default:
		return -EINVAL;
	}
	mask |= PCM_INF2_18WL;
	snd_soc_update_bits(codec, PM860X_PCM_IFACE_2, mask, inf);


	switch (params_rate(params)) {
	case 8000:
		inf = 0;
		break;
	case 16000:
		inf = 3;
		break;
	case 32000:
		inf = 6;
		break;
	case 48000:
		inf = 8;
		break;
	default:
		return -EINVAL;
	}
	snd_soc_update_bits(codec, PM860X_PCM_RATE, 0x0f, inf);

	return 0;
}
