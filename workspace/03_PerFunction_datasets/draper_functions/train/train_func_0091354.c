snd_emu10k1_pcm_channel_alloc(struct snd_emu10k1_pcm * epcm, int voices)
{
	int err, i;

	if (epcm->voices[1] != NULL && voices < 2) {
		snd_emu10k1_voice_free(epcm->emu, epcm->voices[1]);
		epcm->voices[1] = NULL;
	}
	for (i = 0; i < voices; i++) {
		if (epcm->voices[i] == NULL)
			break;
	}
	if (i == voices)
		return 0;

	for (i = 0; i < ARRAY_SIZE(epcm->voices); i++) {
		if (epcm->voices[i]) {
			snd_emu10k1_voice_free(epcm->emu, epcm->voices[i]);
			epcm->voices[i] = NULL;
		}
	}
	err = snd_emu10k1_voice_alloc(epcm->emu,
				      epcm->type == PLAYBACK_EMUVOICE ? EMU10K1_PCM : EMU10K1_EFX,
				      voices,
				      &epcm->voices[0]);

	if (err < 0)
		return err;
	epcm->voices[0]->epcm = epcm;
	if (voices > 1) {
		for (i = 1; i < voices; i++) {
			epcm->voices[i] = &epcm->emu->voices[epcm->voices[0]->number + i];
			epcm->voices[i]->epcm = epcm;
		}
	}
	if (epcm->extra == NULL) {
		err = snd_emu10k1_voice_alloc(epcm->emu,
					      epcm->type == PLAYBACK_EMUVOICE ? EMU10K1_PCM : EMU10K1_EFX,
					      1,
					      &epcm->extra);
		if (err < 0) {


			for (i = 0; i < voices; i++) {
				snd_emu10k1_voice_free(epcm->emu, epcm->voices[i]);
				epcm->voices[i] = NULL;
			}
			return err;
		}
		epcm->extra->epcm = epcm;
		epcm->extra->interrupt = snd_emu10k1_pcm_interrupt;
	}
	return 0;
}
