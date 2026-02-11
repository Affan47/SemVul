nvkm_dma_oclass_fifo_get(struct nvkm_oclass *oclass, int index)
{
	const int count = ARRAY_SIZE(nvkm_dma_sclass);
	if (index < count) {
		oclass->base = nvkm_dma_sclass[index];
		return index;
	}
	return count;
}
