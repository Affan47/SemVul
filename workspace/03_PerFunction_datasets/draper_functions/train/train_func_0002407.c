nvkm_oproxy_sclass(struct nvkm_object *object, int index,
		   struct nvkm_oclass *oclass)
{
	struct nvkm_oproxy *oproxy = nvkm_oproxy(object);
	oclass->parent = oproxy->object;
	if (!oproxy->object->func->sclass)
		return -ENODEV;
	return oproxy->object->func->sclass(oproxy->object, index, oclass);
}
