nv04_gr_idle(struct nvkm_gr *gr)
{
	struct nvkm_subdev *subdev = &gr->engine.subdev;
	struct nvkm_device *device = subdev->device;
	u32 mask = 0xffffffff;

	if (device->card_type == NV_40)
		mask &= ~NV40_PGRAPH_STATUS_SYNC_STALL;

	if (nvkm_msec(device, 2000,
		if (!(nvkm_rd32(device, NV04_PGRAPH_STATUS) & mask))
			break;
	) < 0) {
		nvkm_error(subdev, "idle timed out with status %08x\n",
			   nvkm_rd32(device, NV04_PGRAPH_STATUS));
		return false;
	}

	return true;
}
