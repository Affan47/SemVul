nvkm_ioctl_del(struct nvkm_object *object, void *data, u32 size)
{
	union {
		struct nvif_ioctl_del none;
	} *args = data;
	int ret;

	nvif_ioctl(object, "delete size %d\n", size);
	if (nvif_unvers(args->none)) {
		nvif_ioctl(object, "delete\n");
		nvkm_object_fini(object, false);
		nvkm_object_del(&object);
	}

	return ret;
}
