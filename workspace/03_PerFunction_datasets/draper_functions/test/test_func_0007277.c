nvkm_ioctl_ntfy_new(struct nvkm_object *object, void *data, u32 size)
{
	union {
		struct nvif_ioctl_ntfy_new_v0 v0;
	} *args = data;
	struct nvkm_event *event;
	int ret;

	nvif_ioctl(object, "ntfy new size %d\n", size);
	if (nvif_unpack(args->v0, 0, 0, true)) {
		nvif_ioctl(object, "ntfy new vers %d event %02x\n",
			   args->v0.version, args->v0.event);
		ret = nvkm_object_ntfy(object, args->v0.event, &event);
		if (ret == 0) {
			ret = nvkm_client_notify_new(object, event, data, size);
			if (ret >= 0) {
				args->v0.index = ret;
				ret = 0;
			}
		}
	}

	return ret;
}
