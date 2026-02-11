nvkm_udevice_time(struct nvkm_udevice *udev, void *data, u32 size)
{
	struct nvkm_device *device = udev->device;
	union {
		struct nv_device_time_v0 v0;
	} *args = data;
	int ret;

	if (nvif_unpack(args->v0, 0, 0, false)) {
		args->v0.time = nvkm_timer_read(device->timer);
	}

	return ret;
}
