hw_rule_rate(struct snd_pcm_hw_params *params, struct snd_pcm_hw_rule *rule)
{
	unsigned int *pcm_channels = rule->private;
	struct snd_interval *r =
		hw_param_interval(params, SNDRV_PCM_HW_PARAM_RATE);
	const struct snd_interval *c =
		hw_param_interval_c(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	struct snd_interval t = {
		.min = UINT_MAX, .max = 0, .integer = 1
	};
	unsigned int i, mode;

	for (i = 0; i < ARRAY_SIZE(freq_table); i++) {
		mode = get_multiplier_mode_with_index(i);
		if (!snd_interval_test(c, pcm_channels[mode]))
			continue;

		t.min = min(t.min, freq_table[i]);
		t.max = max(t.max, freq_table[i]);
	}

	return snd_interval_refine(r, &t);
}
