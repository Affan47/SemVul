gt215_devinit_mmio(struct nvkm_devinit *base, u32 addr)
{
	struct nv50_devinit *init = nv50_devinit(base);
	struct nvkm_device *device = init->base.subdev.device;
	u32 *mmio = gt215_devinit_mmio_part;


	while (mmio[0]) {
		if (addr >= mmio[0] && addr <= mmio[1]) {
			u32 part = (addr / mmio[2]) & 7;
			if (!init->r001540)
				init->r001540 = nvkm_rd32(device, 0x001540);
			if (part >= hweight8((init->r001540 >> 16) & 0xff))
				return ~0;
			return addr;
		}
		mmio += 3;
	}

	return addr;
}
