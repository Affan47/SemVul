bios_10_0bxx(struct regs *regs)
{
#ifdef DEBUG_INT10
        dprintf("VGA Function 0b: Set background color or palette.\n");
#endif

	if (BH != 0x00 && BH != 0x01) {
		assert(0);

	} else {
		unsigned char al;
		unsigned char cl;

		(void) inb(0x3da);

		if (BH == 0x00) {
			outb(0x00, 0x3c0);
			al = BL & 0x0f;
			if (al & 0x08) {
				al += 0x08;
			}
			outb(al, 0x3c0);
		}

		for (cl = 0x01; cl != 0x04; cl++) {
			outb(cl, 0x3c0);
			al = inb(0x3c1);
			al &= 0xef;
			al |= BL & 0x10;
			outb(al, 0x3c0);
		}

		outb(0x20, 0x3c0);
	}
}
