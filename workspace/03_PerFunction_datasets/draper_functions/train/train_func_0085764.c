snd_sonicvibes_midi(struct sonicvibes *sonic,
			       struct snd_rawmidi *rmidi)
{
	struct snd_mpu401 * mpu = rmidi->private_data;
	struct snd_card *card = sonic->card;
	struct snd_rawmidi_str *dir;
	unsigned int idx;
	int err;

	mpu->private_data = sonic;
	mpu->open_input = snd_sonicvibes_midi_input_open;
	mpu->close_input = snd_sonicvibes_midi_input_close;
	dir = &rmidi->streams[SNDRV_RAWMIDI_STREAM_OUTPUT];
	for (idx = 0; idx < ARRAY_SIZE(snd_sonicvibes_midi_controls); idx++)
		if ((err = snd_ctl_add(card, snd_ctl_new1(&snd_sonicvibes_midi_controls[idx], sonic))) < 0)
			return err;
	return 0;
}
