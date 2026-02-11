snd_hdspm_hw_rule_in_channels_rate(struct snd_pcm_hw_params *params,
					   struct snd_pcm_hw_rule *rule)
{
	struct hdspm *hdspm = rule->private;
	struct snd_interval *c =
	    hw_param_interval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	struct snd_interval *r =
	    hw_param_interval(params, SNDRV_PCM_HW_PARAM_RATE);

	if (r->min > 96000 && r->max <= 192000) {
		struct snd_interval t = {
			.min = hdspm->qs_in_channels,
			.max = hdspm->qs_in_channels,
			.integer = 1,
		};
		return snd_interval_refine(c, &t);
	} else if (r->min > 48000 && r->max <= 96000) {
		struct snd_interval t = {
			.min = hdspm->ds_in_channels,
			.max = hdspm->ds_in_channels,
			.integer = 1,
		};
		return snd_interval_refine(c, &t);
	} else if (r->max < 64000) {
		struct snd_interval t = {
			.min = hdspm->ss_in_channels,
			.max = hdspm->ss_in_channels,
			.integer = 1,
		};
		return snd_interval_refine(c, &t);
	}

	return 0;
}
