CFontzPacket_output(Driver *drvthis, int state)
{
	static const unsigned char CFontz635_LEDs[CF635_NUM_LEDs] = {
		11, 9, 7, 5,
		12,10, 8, 6,
	};
	PrivateData *p = drvthis->private_data;
	unsigned char out[2];
	int lednum;

	if (p->model != 635)
		return;

	for (lednum = 0; lednum < CF635_NUM_LEDs; lednum++) {
		unsigned int mask = (1 << lednum);
		int on_off = (state & mask);

		if ((p->LEDstate & mask) != on_off) {
			out[0] = CFontz635_LEDs[lednum];
			out[1] = (on_off == 0) ? 0 : 100;
			send_bytes_message(p->fd, CF633_Set_GPIO_Pin, 2, out);
		}
	}
	p->LEDstate = state;
}
