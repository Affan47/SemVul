twl4030_audio_set_resource(enum twl4030_audio_res id, int enable)
{
	struct twl4030_audio *audio = platform_get_drvdata(twl4030_audio_dev);
	u8 val;

	twl_i2c_read_u8(TWL4030_MODULE_AUDIO_VOICE, &val,
			audio->resource[id].reg);

	if (enable)
		val |= audio->resource[id].mask;
	else
		val &= ~audio->resource[id].mask;

	twl_i2c_write_u8(TWL4030_MODULE_AUDIO_VOICE,
					val, audio->resource[id].reg);

	return val;
}
