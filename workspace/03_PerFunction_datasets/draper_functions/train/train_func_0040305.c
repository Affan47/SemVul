init_zm_reg(struct nvbios_init *init)
{
	struct nvkm_bios *bios = init->bios;
	u32 addr = nvbios_rd32(bios, init->offset + 1);
	u32 data = nvbios_rd32(bios, init->offset + 5);

	trace("ZM_REG\tR[0x%06x] = 0x%08x\n", addr, data);
	init->offset += 9;

	if (addr == 0x000200)
		data |= 0x00000001;

	init_wr32(init, addr, data);
}
