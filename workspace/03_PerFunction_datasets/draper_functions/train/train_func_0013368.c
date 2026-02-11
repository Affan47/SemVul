match_endpoint_audioformats(struct snd_usb_substream *subs,
				       struct audioformat *fp,
				       struct audioformat *match, int rate,
				       snd_pcm_format_t pcm_format)
{
	int i;
	int score = 0;

	if (fp->channels < 1) {
		dev_dbg(&subs->dev->dev,
			"%s: (fmt @%p) no channels\n", __func__, fp);
		return 0;
	}

	if (!(fp->formats & pcm_format_to_bits(pcm_format))) {
		dev_dbg(&subs->dev->dev,
			"%s: (fmt @%p) no match for format %d\n", __func__,
			fp, pcm_format);
		return 0;
	}

	for (i = 0; i < fp->nr_rates; i++) {
		if (fp->rate_table[i] == rate) {
			score++;
			break;
		}
	}
	if (!score) {
		dev_dbg(&subs->dev->dev,
			"%s: (fmt @%p) no match for rate %d\n", __func__,
			fp, rate);
		return 0;
	}

	if (fp->channels == match->channels)
		score++;

	dev_dbg(&subs->dev->dev,
		"%s: (fmt @%p) score %d\n", __func__, fp, score);

	return score;
}
