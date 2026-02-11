ide_harddisk_write_lba(
	uint8_t controller,
	uint8_t unit,
	uint8_t num,
	uint32_t  start,
	uint16_t buffer_seg,
	uint16_t buffer_off)
{
	uint16_t port;
	uint8_t status;

	assert( controller < 6);
	assert( unit < 2);


	port = const_get(ide_port_table[controller]);


	do {
		status = inb(port + 0x206);
	} while (status & IDE_BUSY_STAT);


	outb(num, port + 2);
	outb((start >> 0) & 0xff, port + 3);
	outb((start >> 8) & 0xff, port + 4);
	outb((start >> 16) & 0xff, port + 5);
	outb(0xe0 | (unit << 4) | ((start >> 24) & 0xf), port + 6);

	outb(0x30, port + 7);


	do {
		status = inb(port + 0x206);
	} while (status & IDE_BUSY_STAT);


	for ( ; 0 < num; num--) {
		uint16_t count;
		uint16_t data;

		if (! (status & IDE_DRQ_STAT)) {

			assert(0);
			return 0xff;
		}


		buffer_seg += buffer_off / 16;
		buffer_off %= 16;

		for (count = 0; count < 512 / 2; count++) {
			data = get_word(buffer_seg, buffer_off + count * 2);
			outw(data, port);
		}

		buffer_seg += 512 / 16;


		do {
			status = inb(port + 0x206);
		} while (status & IDE_BUSY_STAT);

		if (status & IDE_ERR_STAT) {

			return 0xff;
		}
	}

	return 0;
}
