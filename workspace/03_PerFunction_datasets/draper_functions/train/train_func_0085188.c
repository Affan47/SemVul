gk104_ram_nuts(struct gk104_ram *ram, struct ramfuc_reg *reg,
	       u32 _mask, u32 _data, u32 _copy)
{
	struct nvkm_fb *fb = ram->base.fb;
	struct ramfuc *fuc = &ram->fuc.base;
	struct nvkm_device *device = fb->subdev.device;
	u32 addr = 0x110000 + (reg->addr & 0xfff);
	u32 mask = _mask | _copy;
	u32 data = (_data & _mask) | (reg->data & _copy);
	u32 i;

	for (i = 0; i < 16; i++, addr += 0x1000) {
		if (ram->pnuts & (1 << i)) {
			u32 prev = nvkm_rd32(device, addr);
			u32 next = (prev & ~mask) | data;
			nvkm_memx_wr32(fuc->memx, addr, next);
		}
	}
}
