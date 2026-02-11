update_pcm1796_mute(struct oxygen *chip)
{
	struct xonar_pcm179x *data = chip->model_data;
	unsigned int i;
	u8 value;

	value = PCM1796_DMF_DISABLED | PCM1796_FMT_24_I2S | PCM1796_ATLD;
	if (chip->dac_mute)
		value |= PCM1796_MUTE;
	for (i = 0; i < data->dacs; ++i)
		pcm1796_write_cached(chip, i, 18, value);
}
