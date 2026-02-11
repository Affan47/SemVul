lola_pcm_update(struct lola *chip, struct lola_pcm *pcm, unsigned int bits)
{
	int i;

	for (i = 0; bits && i < pcm->num_streams; i++) {
		if (bits & (1 << i)) {
			struct lola_stream *str = &pcm->streams[i];
			if (str->substream && str->running)
				snd_pcm_period_elapsed(str->substream);
			bits &= ~(1 << i);
		}
	}
}
