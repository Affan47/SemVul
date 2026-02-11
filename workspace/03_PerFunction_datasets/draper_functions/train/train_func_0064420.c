snd_midi_channel_init(struct snd_midi_channel *p, int n)
{
	if (p == NULL)
		return;

	memset(p, 0, sizeof(struct snd_midi_channel));
	p->private = NULL;
	p->number = n;

	snd_midi_reset_controllers(p);
	p->gm_rpn_pitch_bend_range = 256;
	p->gm_rpn_fine_tuning = 0;
	p->gm_rpn_coarse_tuning = 0;

	if (n == 9)
		p->drum_channel = 1;
}
