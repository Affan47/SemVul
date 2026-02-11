uninit(int immed)
{
	if (alsa_handler) {
		if (s_pcm_drop(alsa_handler) < 0) {
			return;
		}

		if (s_pcm_close(alsa_handler) < 0)
		{
			return;
		} else {
			alsa_handler = NULL;
		}
	}
}
