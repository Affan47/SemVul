amradio_set_freq(struct amradio_device *radio, int freq)
{
	unsigned short freq_send;
	u8 buf[3];
	int retval;


	freq = clamp_t(unsigned, freq, FREQ_MIN * FREQ_MUL, FREQ_MAX * FREQ_MUL);
	freq_send = 0x10 + (freq >> 3) / 25;


	buf[0] = (freq_send >> 8) & 0xff;
	buf[1] = freq_send & 0xff;
	buf[2] = 0x01;

	retval = amradio_send_cmd(radio, AMRADIO_SET_FREQ, 0, buf, 3, false);
	if (retval)
		return retval;
	radio->curfreq = freq;
	msleep(40);
	return 0;
}
