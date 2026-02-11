nv50_instobj_wr32(struct nvkm_memory *memory, u64 offset, u32 data)
{
	struct nv50_instobj *iobj = nv50_instobj(memory);
	struct nv50_instmem *imem = iobj->imem;
	struct nvkm_device *device = imem->base.subdev.device;
	u64 base = (iobj->mem->offset + offset) & 0xffffff00000ULL;
	u64 addr = (iobj->mem->offset + offset) & 0x000000fffffULL;

	if (unlikely(imem->addr != base)) {
		nvkm_wr32(device, 0x001700, base >> 16);
		imem->addr = base;
	}
	nvkm_wr32(device, 0x700000 + addr, data);
}
