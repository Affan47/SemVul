floppy_init(void)
{
	uint8_t drive_type;
	uint16_t equipment;


	outb(0x08, 0x3f2);
	outb(0x0c, 0x3f2);


	outb(0x08, 0x3f5);


	(void) inb(0x3f5);
	(void) inb(0x3f5);


	outb(0x13, 0x3f5);
	outb(0x00, 0x3f5);
	outb(0 << 7
	   | 1 << 6
	   | 1 << 5
	   | 1 << 4
	   | 0 << 0,
		0x3f5);
	outb(0x00, 0x3f5);


	put_word(0x0000, 0x1e * 4 + 0, PTR_OFF(&diskette_param_table));
	put_word(0x0000, 0x1e * 4 + 2, PTR_SEG(&diskette_param_table));


	drive_type = cmos_get(fd_config);
	equipment = var_get(sys_conf) & ~0xc1;
	if ((drive_type >> 4) & 0xf) {
		equipment |= (1 << 0);
	}
	if ((drive_type >> 0) & 0xf) {
		equipment |= (1 << 6);
	}
	var_put(sys_conf, equipment);
}
