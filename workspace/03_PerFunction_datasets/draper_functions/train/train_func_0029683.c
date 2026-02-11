nvkm_dma_oclass_base_get(struct nvkm_oclass *sclass, int index,
			 const struct nvkm_device_oclass **class)
{
	const int count = ARRAY_SIZE(nvkm_dma_sclass);
	if (index < count) {
		const struct nvkm_sclass *oclass = &nvkm_dma_sclass[index];
		sclass->base = oclass[0];
		sclass->engn = oclass;
		*class = &nvkm_dma_oclass_base;
		return index;
	}
	return count;
}
