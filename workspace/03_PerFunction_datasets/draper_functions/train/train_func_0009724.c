r1373f4_fini(struct gk104_ramfuc *fuc)
{
	struct gk104_ram *ram = container_of(fuc, typeof(*ram), fuc);
	struct nvkm_ram_data *next = ram->base.next;
	u8 v0 = next->bios.ramcfg_11_03_c0;
	u8 v1 = next->bios.ramcfg_11_03_30;
	u32 tmp;

	tmp = ram_rd32(fuc, 0x1373ec) & ~0x00030000;
	ram_wr32(fuc, 0x1373ec, tmp | (v1 << 16));
	ram_mask(fuc, 0x1373f0, (~ram->mode & 3), 0x00000000);
	if (ram->mode == 2) {
		ram_mask(fuc, 0x1373f4, 0x00000003, 0x000000002);
		ram_mask(fuc, 0x1373f4, 0x00001100, 0x000000000);
	} else {
		ram_mask(fuc, 0x1373f4, 0x00000003, 0x000000001);
		ram_mask(fuc, 0x1373f4, 0x00010000, 0x000000000);
	}
	ram_mask(fuc, 0x10f800, 0x00000030, (v0 ^ v1) << 4);
}
