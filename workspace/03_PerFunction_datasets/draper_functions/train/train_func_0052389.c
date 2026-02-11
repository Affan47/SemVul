get_sync_mode(struct snd_bebob *bebob, enum cip_flags *sync_mode)
{
	enum snd_bebob_clock_type src;
	int err;

	err = snd_bebob_stream_get_clock_src(bebob, &src);
	if (err < 0)
		return err;

	switch (src) {
	case SND_BEBOB_CLOCK_TYPE_INTERNAL:
	case SND_BEBOB_CLOCK_TYPE_EXTERNAL:
		*sync_mode = CIP_SYNC_TO_DEVICE;
		break;
	default:
	case SND_BEBOB_CLOCK_TYPE_SYT:
		*sync_mode = 0;
		break;
	}

	return 0;
}
