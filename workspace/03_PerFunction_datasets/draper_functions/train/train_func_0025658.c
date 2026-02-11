msp_set_source(struct i2c_client *client, u16 src)
{
	struct msp_state *state = to_state(i2c_get_clientdata(client));

	if (msp_dolby) {
		msp_write_dsp(client, 0x0008, 0x0520);
		msp_write_dsp(client, 0x0009, 0x0620);
	} else {
		msp_write_dsp(client, 0x0008, src);
		msp_write_dsp(client, 0x0009, src);
	}
	msp_write_dsp(client, 0x000a, src);
	msp_write_dsp(client, 0x000b, src);
	msp_write_dsp(client, 0x000c, src);
	if (state->has_scart2_out)
		msp_write_dsp(client, 0x0041, src);
}
