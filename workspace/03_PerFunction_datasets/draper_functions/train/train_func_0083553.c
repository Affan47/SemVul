snd_soc_dpcm_can_be_free_stop(struct snd_soc_pcm_runtime *fe,
		struct snd_soc_pcm_runtime *be, int stream)
{
	struct snd_soc_dpcm *dpcm;
	int state;

	list_for_each_entry(dpcm, &be->dpcm[stream].fe_clients, list_fe) {

		if (dpcm->fe == fe)
			continue;

		state = dpcm->fe->dpcm[stream].state;
		if (state == SND_SOC_DPCM_STATE_START ||
			state == SND_SOC_DPCM_STATE_PAUSED ||
			state == SND_SOC_DPCM_STATE_SUSPEND)
			return 0;
	}


	return 1;
}
