nvkm_gpuobj_acquire(struct nvkm_gpuobj *gpuobj)
{
	gpuobj->map = nvkm_kmap(gpuobj->parent);
	if (likely(gpuobj->map)) {
		gpuobj->map  = (u8 *)gpuobj->map + gpuobj->node->offset;
		gpuobj->func = &nvkm_gpuobj_fast;
	} else {
		gpuobj->func = &nvkm_gpuobj_slow;
	}
	return gpuobj->map;
}
