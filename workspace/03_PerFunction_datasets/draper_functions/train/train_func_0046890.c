writebuf(snd_pcm_t *handle, char *buf, long len)
{
	snd_pcm_sframes_t r;

	while (1) {
		r = snd_pcm_writei(handle, buf, len);
		if (r == len)
			return 0;
		if (r < 0) {
			r = snd_pcm_recover(handle, r, 0);
			if (r < 0) {
				fprintf(error_fp, "alsa: underrun recover error: %s\n",
					snd_strerror(r));
				return r;
			}
		}
		buf += r * 4;
		len -= r;
		snd_pcm_wait(handle, 100);
	}
}
