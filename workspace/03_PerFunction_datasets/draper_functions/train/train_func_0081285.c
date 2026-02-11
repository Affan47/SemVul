nv31_mpeg_mthd(struct nv31_mpeg *mpeg, u32 mthd, u32 data)
{
	struct nvkm_device *device = mpeg->engine.subdev.device;
	switch (mthd) {
	case 0x190:
	case 0x1a0:
	case 0x1b0:
		return mpeg->func->mthd_dma(device, mthd, data);
	default:
		break;
	}
	return false;
}
