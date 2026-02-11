cx23885_set_audclk_freq(struct i2c_client *client, u32 freq)
{
	struct cx25840_state *state = to_state(i2c_get_clientdata(client));

	if (state->aud_input != CX25840_AUDIO_SERIAL) {
		switch (freq) {
		case 32000:
		case 44100:
		case 48000:


			break;
		}
	} else {
		switch (freq) {
		case 32000:
		case 44100:


			break;

		case 48000:


			cx25840_write4(client, 0x8f8, 0x0801867c);


			cx25840_write4(client, 0x900, 0x08014faa);
			cx25840_write4(client, 0x904, 0x08014faa);
			cx25840_write4(client, 0x90c, 0x08014faa);
			break;
		}
	}

	state->audclk_freq = freq;

	return 0;
}
