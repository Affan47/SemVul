pcm512x_hw_rule_rate(struct snd_pcm_hw_params *params,
				struct snd_pcm_hw_rule *rule)
{
	struct pcm512x_priv *pcm512x = rule->private;
	struct snd_interval ranges[2];
	int frame_size;

	frame_size = snd_soc_params_to_frame_size(params);
	if (frame_size < 0)
		return frame_size;

	switch (frame_size) {
	case 32:

		return 0;
	case 48:
	case 64:


		memset(ranges, 0, sizeof(ranges));
		ranges[0].min = 8000;
		ranges[0].max = pcm512x_sck_max(pcm512x) / frame_size / 2;
		ranges[1].min = DIV_ROUND_UP(16000000, frame_size);
		ranges[1].max = 384000;
		break;
	default:
		return -EINVAL;
	}

	return snd_interval_ranges(hw_param_interval(params, rule->var),
				   ARRAY_SIZE(ranges), ranges, 0);
}
