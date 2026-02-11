init_zm_cr_group(struct nvbios_init *init)
{
	struct nvkm_bios *bios = init->bios;
	u8 count = nvbios_rd08(bios, init->offset + 1);

	trace("ZM_CR_GROUP\n");
	init->offset += 2;

	while (count--) {
		u8 addr = nvbios_rd08(bios, init->offset + 0);
		u8 data = nvbios_rd08(bios, init->offset + 1);

		trace("\t\tC[0x%02x] = 0x%02x\n", addr, data);
		init->offset += 2;

		init_wrvgai(init, 0x03d4, addr, data);
	}
}
