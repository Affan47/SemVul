Sync()
{
	int prglo;
	int prghi;

	int outb = outer << 1;


	switch (mode & 0x3c)
	{

	case 0x00:
	case 0x04:
		prglo = outb;
		prghi = outb | 1;
		break;
	case 0x10:
	case 0x14:
		prglo = outb & ~2 | prg << 1 & 2;
		prghi = outb & ~2 | prg << 1 & 2 | 1;
		break;
	case 0x20:
	case 0x24:
		prglo = outb & ~6 | prg << 1 & 6;
		prghi = outb & ~6 | prg << 1 & 6 | 1;
		break;
	case 0x30:
	case 0x34:
		prglo = outb & ~14 | prg << 1 & 14;
		prghi = outb & ~14 | prg << 1 & 14 | 1;
		break;

	case 0x08:
		prglo = outb;
		prghi = outb | prg & 1;
		break;
	case 0x18:
		prglo = outb;
		prghi = outb & ~2 | prg & 3;
		break;
	case 0x28:
		prglo = outb;
		prghi = outb & ~6 | prg & 7;
		break;
	case 0x38:
		prglo = outb;
		prghi = outb & ~14 | prg & 15;
		break;

	case 0x0c:
		prglo = outb | prg & 1;
		prghi = outb | 1;
		break;
	case 0x1c:
		prglo = outb & ~2 | prg & 3;
		prghi = outb | 1;
		break;
	case 0x2c:
		prglo = outb & ~6 | prg & 7;
		prghi = outb | 1;
		break;
	case 0x3c:
		prglo = outb & ~14 | prg & 15;
		prghi = outb | 1;
		break;
	}
	prglo &= prg_mask_16k;
	prghi &= prg_mask_16k;

	setprg16(0x8000, prglo);
	setprg16(0xC000, prghi);
	setchr8(chr);
}
