wl1273_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct wl1273_priv *wl1273 = snd_soc_codec_get_drvdata(dai->codec);
	struct wl1273_core *core = wl1273->core;
	unsigned int rate, width, r;

	if (params_width(params) != 16) {
		dev_err(dai->dev, "%d bits/sample not supported\n",
			params_width(params));
		return -EINVAL;
	}

	rate = params_rate(params);
	width =  hw_param_interval(params, SNDRV_PCM_HW_PARAM_SAMPLE_BITS)->min;

	if (wl1273->mode == WL1273_MODE_BT) {
		if (rate != 8000) {
			pr_err("Rate %d not supported.\n", params_rate(params));
			return -EINVAL;
		}

		if (params_channels(params) != 1) {
			pr_err("Only mono supported.\n");
			return -EINVAL;
		}

		return 0;
	}

	if (wl1273->mode == WL1273_MODE_FM_TX &&
	    substream->stream == SNDRV_PCM_STREAM_CAPTURE) {
		pr_err("Only playback supported with TX.\n");
		return -EINVAL;
	}

	if (wl1273->mode == WL1273_MODE_FM_RX  &&
	    substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		pr_err("Only capture supported with RX.\n");
		return -EINVAL;
	}

	if (wl1273->mode != WL1273_MODE_FM_RX  &&
	    wl1273->mode != WL1273_MODE_FM_TX) {
		pr_err("Unexpected mode: %d.\n", wl1273->mode);
		return -EINVAL;
	}

	r = snd_wl1273_fm_set_i2s_mode(core, rate, width);
	if (r)
		return r;

	wl1273->channels = params_channels(params);
	r = snd_wl1273_fm_set_channel_number(core, wl1273->channels);
	if (r)
		return r;

	return 0;
}
