init_io_restrict_pll(struct nvbios_init *init)
{
	struct nvkm_bios *bios = init->bios;
	u16 port = nvbios_rd16(bios, init->offset + 1);
	u8 index = nvbios_rd08(bios, init->offset + 3);
	u8  mask = nvbios_rd08(bios, init->offset + 4);
	u8 shift = nvbios_rd08(bios, init->offset + 5);
	s8  iofc = nvbios_rd08(bios, init->offset + 6);
	u8 count = nvbios_rd08(bios, init->offset + 7);
	u32  reg = nvbios_rd32(bios, init->offset + 8);
	u8 conf, i;

	trace("IO_RESTRICT_PLL\tR[0x%06x] =PLL= "
	      "((0x%04x[0x%02x] & 0x%02x) >> 0x%02x) IOFCOND 0x%02x [{\n",
	      reg, port, index, mask, shift, iofc);
	init->offset += 12;

	conf = (init_rdvgai(init, port, index) & mask) >> shift;
	for (i = 0; i < count; i++) {
		u32 freq = nvbios_rd16(bios, init->offset) * 10;

		if (i == conf) {
			trace("\t%dkHz *\n", freq);
			if (iofc > 0 && init_io_flag_condition_met(init, iofc))
				freq *= 2;
			init_prog_pll(init, reg, freq);
		} else {
			trace("\t%dkHz\n", freq);
		}

		init->offset += 2;
	}
	trace("}]\n");
}
