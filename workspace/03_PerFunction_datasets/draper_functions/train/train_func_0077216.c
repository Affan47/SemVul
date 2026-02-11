wm5100_alloc_sr(struct snd_soc_codec *codec, int rate)
{
	struct wm5100_priv *wm5100 = snd_soc_codec_get_drvdata(codec);
	int sr_code, sr_free, i;

	for (i = 0; i < ARRAY_SIZE(wm5100_sr_code); i++)
		if (wm5100_sr_code[i] == rate)
			break;
	if (i == ARRAY_SIZE(wm5100_sr_code)) {
		dev_err(codec->dev, "Unsupported sample rate: %dHz\n", rate);
		return -EINVAL;
	}
	sr_code = i;

	if ((wm5100->sysclk % rate) == 0) {

		sr_free = -1;
		for (i = 0; i < ARRAY_SIZE(wm5100_sr_regs); i++) {
			if (!wm5100->sr_ref[i] && sr_free == -1) {
				sr_free = i;
				continue;
			}
			if ((snd_soc_read(codec, wm5100_sr_regs[i]) &
			     WM5100_SAMPLE_RATE_1_MASK) == sr_code)
				break;
		}

		if (i < ARRAY_SIZE(wm5100_sr_regs)) {
			wm5100->sr_ref[i]++;
			dev_dbg(codec->dev, "SR %dHz, slot %d, ref %d\n",
				rate, i, wm5100->sr_ref[i]);
			return i;
		}

		if (sr_free == -1) {
			dev_err(codec->dev, "All SR slots already in use\n");
			return -EBUSY;
		}

		dev_dbg(codec->dev, "Allocating SR slot %d for %dHz\n",
			sr_free, rate);
		wm5100->sr_ref[sr_free]++;
		snd_soc_update_bits(codec, wm5100_sr_regs[sr_free],
				    WM5100_SAMPLE_RATE_1_MASK,
				    sr_code);

		return sr_free;

	} else {
		dev_err(codec->dev,
			"SR %dHz incompatible with %dHz SYSCLK and %dHz ASYNCCLK\n",
			rate, wm5100->sysclk, wm5100->asyncclk);
		return -EINVAL;
	}
}
