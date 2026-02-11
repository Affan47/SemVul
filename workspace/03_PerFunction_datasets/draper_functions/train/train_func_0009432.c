gdb_reader_loop(struct gdb_data *data)
{
	for (;;) {
		char buf[MAX_MEM_XFER * 2 + 64];
		int len = 0;
		int cksum_calc = 0;
		int cksum_recv = 0;
		int c;


		do {
			c = gdb_getc(data);
			if (c < 0)
				return;
		} while (c != '$');


		while (len + 1 < sizeof(buf)) {
			c = gdb_getc(data);
			if (c < 0)
				return;
			if (c == '#')
				break;

			buf[len++] = c;
			cksum_calc = (cksum_calc + c) & 0xff;
		}
		buf[len] = 0;


		c = gdb_getc(data);
		if (c < 0)
			return;
		cksum_recv = hexval(c);
		c = gdb_getc(data);
		if (c < 0)
			return;
		cksum_recv = (cksum_recv << 4) | hexval(c);

#ifdef DEBUG_GDB
		printc("<- $%s#%02x\n", buf, cksum_recv);
#endif

		if (cksum_recv != cksum_calc) {
			printc_err("gdb: bad checksum (calc = 0x%02x, "
				"recv = 0x%02x)\n", cksum_calc, cksum_recv);
			printc_err("gdb: packet data was: %s\n", buf);
			gdb_printf(data, "-");
			if (gdb_flush(data) < 0)
				return;
			continue;
		}


		gdb_printf(data, "+");
		if (gdb_flush(data) < 0)
			return;

		if (len && process_gdb_command(data, buf, len) < 0)
			return;
	}
}
