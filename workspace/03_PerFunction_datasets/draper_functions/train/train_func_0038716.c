bios_17_xxxx(struct regs *regs)
{
	if (AH < 3 && DX == 0) {
		uint16_t addr;
		uint16_t timeout;
		uint8_t val8;

		addr = var_get(addr_par[DX]);
		timeout = var_get(par_tmout[DX]) << 8;

		if (AH == 0x00) {
			outb(AL, addr);
			val8 = inb(addr + 2);
			outb(val8 | 0x01, addr + 2);
			asm ("nop");
			outb(val8 & ~0x01, addr + 2);
			while ((inb(addr + 1) & 0x40) == 0x40 && timeout) {
				timeout--;
			}

		} else if (AH == 0x01) {
			val8 = inb(addr + 2);
			outb(val8 & ~0x04, addr + 2);
			asm ("nop");
			outb(val8 | 0x40, addr + 2);

		} else { assert(AH == 0x02);

		}

		AH = inb(addr + 1);
		val8 = ~AH & 0x48;
		AH &= 0xb7;
		AH |= val8;
		if (! timeout) {
			AH |= 0x01;
		}
		F &= ~(1 << 0);

	} else {

		F |= 1 << 0;
	}
}
