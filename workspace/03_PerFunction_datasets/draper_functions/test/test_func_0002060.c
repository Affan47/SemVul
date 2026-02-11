init_sub(struct nvbios_init *init)
{
	struct nvkm_bios *bios = init->bios;
	u8 index = nvbios_rd08(bios, init->offset + 1);
	u16 addr, save;

	trace("SUB\t0x%02x\n", index);

	addr = init_script(bios, index);
	if (addr && init_exec(init)) {
		save = init->offset;
		init->offset = addr;
		if (nvbios_exec(init)) {
			error("error parsing sub-table\n");
			return;
		}
		init->offset = save;
	}

	init->offset += 2;
}
