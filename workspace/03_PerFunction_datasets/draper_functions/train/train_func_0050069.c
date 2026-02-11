gc_n64_send_command(struct gc *gc, unsigned long cmd,
				unsigned char target)
{
	struct parport *port = gc->pd->port;
	int i;

	for (i = 0; i < GC_N64_LENGTH; i++) {
		unsigned char data = (cmd >> i) & 1 ? target : 0;
		parport_write_data(port, GC_N64_POWER_W | data);
		udelay(GC_N64_DWS);
	}
}
