nv50_ram_timing_read(struct nv50_ram *ram, u32 *timing)
{
	unsigned int i;
	struct nvbios_ramcfg *cfg = &ram->base.target.bios;
	struct nvkm_subdev *subdev = &ram->base.fb->subdev;
	struct nvkm_device *device = subdev->device;

	for (i = 0; i <= 8; i++)
		timing[i] = nvkm_rd32(device, 0x100220 + (i * 4));


	cfg->timing_ver = 0x10;
	T(CL) = (timing[3] & 0xff) + 1;

	switch (ram->base.type) {
	case NVKM_RAM_TYPE_DDR2:
		T(CWL) = T(CL) - 1;
		break;
	case NVKM_RAM_TYPE_GDDR3:
		T(CWL) = ((timing[2] & 0xff000000) >> 24) + 1;
		break;
	default:
		return -ENOSYS;
		break;
	}

	T(WR) = ((timing[1] >> 24) & 0xff) - 1 - T(CWL);

	return 0;
}
