nv50_dmaobj_new(struct nvkm_dma *dma, const struct nvkm_oclass *oclass,
		void *data, u32 size, struct nvkm_dmaobj **pdmaobj)
{
	union {
		struct nv50_dma_v0 v0;
	} *args;
	struct nvkm_object *parent = oclass->parent;
	struct nv50_dmaobj *dmaobj;
	u32 user, part, comp, kind;
	int ret;

	if (!(dmaobj = kzalloc(sizeof(*dmaobj), GFP_KERNEL)))
		return -ENOMEM;
	*pdmaobj = &dmaobj->base;

	ret = nvkm_dmaobj_ctor(&nv50_dmaobj_func, dma, oclass,
			       &data, &size, &dmaobj->base);
	if (ret)
		return ret;

	args = data;

	nvif_ioctl(parent, "create nv50 dma size %d\n", size);
	if (nvif_unpack(args->v0, 0, 0, false)) {
		nvif_ioctl(parent, "create nv50 dma vers %d priv %d part %d "
				   "comp %d kind %02x\n", args->v0.version,
			   args->v0.priv, args->v0.part, args->v0.comp,
			   args->v0.kind);
		user = args->v0.priv;
		part = args->v0.part;
		comp = args->v0.comp;
		kind = args->v0.kind;
	} else
	if (size == 0) {
		if (dmaobj->base.target != NV_MEM_TARGET_VM) {
			user = NV50_DMA_V0_PRIV_US;
			part = NV50_DMA_V0_PART_256;
			comp = NV50_DMA_V0_COMP_NONE;
			kind = NV50_DMA_V0_KIND_PITCH;
		} else {
			user = NV50_DMA_V0_PRIV_VM;
			part = NV50_DMA_V0_PART_VM;
			comp = NV50_DMA_V0_COMP_VM;
			kind = NV50_DMA_V0_KIND_VM;
		}
	} else
		return ret;

	if (user > 2 || part > 2 || comp > 3 || kind > 0x7f)
		return -EINVAL;
	dmaobj->flags0 = (comp << 29) | (kind << 22) | (user << 20) |
			 oclass->base.oclass;
	dmaobj->flags5 = (part << 16);

	switch (dmaobj->base.target) {
	case NV_MEM_TARGET_VM:
		dmaobj->flags0 |= 0x00000000;
		break;
	case NV_MEM_TARGET_VRAM:
		dmaobj->flags0 |= 0x00010000;
		break;
	case NV_MEM_TARGET_PCI:
		dmaobj->flags0 |= 0x00020000;
		break;
	case NV_MEM_TARGET_PCI_NOSNOOP:
		dmaobj->flags0 |= 0x00030000;
		break;
	default:
		return -EINVAL;
	}

	switch (dmaobj->base.access) {
	case NV_MEM_ACCESS_VM:
		break;
	case NV_MEM_ACCESS_RO:
		dmaobj->flags0 |= 0x00040000;
		break;
	case NV_MEM_ACCESS_WO:
	case NV_MEM_ACCESS_RW:
		dmaobj->flags0 |= 0x00080000;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
