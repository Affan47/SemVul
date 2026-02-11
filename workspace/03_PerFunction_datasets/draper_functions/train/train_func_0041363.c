memx_out(struct nvkm_memx *memx)
{
	struct nvkm_device *device = memx->pmu->subdev.device;
	int i;

	if (memx->c.mthd) {
		nvkm_wr32(device, 0x10a1c4, (memx->c.size << 16) | memx->c.mthd);
		for (i = 0; i < memx->c.size; i++)
			nvkm_wr32(device, 0x10a1c4, memx->c.data[i]);
		memx->c.mthd = 0;
		memx->c.size = 0;
	}
}
