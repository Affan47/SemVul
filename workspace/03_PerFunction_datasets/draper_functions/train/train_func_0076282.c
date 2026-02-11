nvkm_object_mthd(struct nvkm_object *object, u32 mthd, void *data, u32 size)
{
	if (likely(object->func->mthd))
		return object->func->mthd(object, mthd, data, size);
	return -ENODEV;
}
