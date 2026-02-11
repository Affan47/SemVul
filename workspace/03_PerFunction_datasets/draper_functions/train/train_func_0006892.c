snd_tscm_stream_get_clock(struct snd_tscm *tscm, enum snd_tscm_clock *clock)
{
	u32 data;
	int err;

	err = get_clock(tscm, &data);
	if (err < 0)
		return err;

	*clock = ((data & 0x00ff0000) >> 16) - 1;
	if (*clock < 0 || *clock > SND_TSCM_CLOCK_ADAT)
		return -EIO;

	return 0;
}
