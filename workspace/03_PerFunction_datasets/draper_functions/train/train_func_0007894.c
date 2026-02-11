snd_ymfpci_pcm_voice_alloc(struct snd_ymfpci_pcm *ypcm, int voices)
{
	int err;

	if (ypcm->voices[1] != NULL && voices < 2) {
		snd_ymfpci_voice_free(ypcm->chip, ypcm->voices[1]);
		ypcm->voices[1] = NULL;
	}
	if (voices == 1 && ypcm->voices[0] != NULL)
		return 0;
	if (voices == 2 && ypcm->voices[0] != NULL && ypcm->voices[1] != NULL)
		return 0;
	if (voices > 1) {
		if (ypcm->voices[0] != NULL && ypcm->voices[1] == NULL) {
			snd_ymfpci_voice_free(ypcm->chip, ypcm->voices[0]);
			ypcm->voices[0] = NULL;
		}
	}
	err = snd_ymfpci_voice_alloc(ypcm->chip, YMFPCI_PCM, voices > 1, &ypcm->voices[0]);
	if (err < 0)
		return err;
	ypcm->voices[0]->ypcm = ypcm;
	ypcm->voices[0]->interrupt = snd_ymfpci_pcm_interrupt;
	if (voices > 1) {
		ypcm->voices[1] = &ypcm->chip->voices[ypcm->voices[0]->number + 1];
		ypcm->voices[1]->ypcm = ypcm;
	}
	return 0;
}
