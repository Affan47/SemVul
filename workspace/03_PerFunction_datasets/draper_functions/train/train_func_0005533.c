mem_read(int a)
{
	int n;
	byte ha = (a>>12) & 0xE;


	switch (ha)
	{
	case 0x0:
	case 0x2:
		return rom.bank[0][a];
	case 0x4:
	case 0x6:
		return rom.bank[mbc.rombank][a & 0x3FFF];
	case 0x8:

		return lcd.vbank[R_VBK&1][a & 0x1FFF];
	case 0xA:
		if (!mbc.enableram && mbc.type == MBC_HUC3)
			return 0x01;
		if (!mbc.enableram)
			return 0xFF;
		if (rtc.sel&8)
			return rtc.regs[rtc.sel&7];
		return ram.sbank[mbc.rambank][a & 0x1FFF];
	case 0xC:
		if ((a & 0xF000) == 0xC000)
			return ram.ibank[0][a & 0x0FFF];
		n = R_SVBK & 0x07;
		return ram.ibank[n?n:1][a & 0x0FFF];
	case 0xE:
		if (a < 0xFE00) return mem_read(a & 0xDFFF);
		if ((a & 0xFF00) == 0xFE00)
		{

			if (a < 0xFEA0) return lcd.oam.mem[a & 0xFF];
			return 0xFF;
		}

		if (a == 0xFFFF) return REG(0xFF);
		if (a >= 0xFF10 && a <= 0xFF3F)
			return sound_read(a & 0xFF);
		if ((a & 0xFF80) == 0xFF80)
			return ram.hi[a & 0xFF];
		return ioreg_read(a & 0xFF);
	}
	return 0xff;
}
