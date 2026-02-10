nvkm_xtensa_new_(const struct nvkm_xtensa_func *func,
		 struct nvkm_device *device, int index, bool enable,
		 u32 addr, struct nvkm_engine **pengine)
{
	struct nvkm_xtensa *xtensa;

	if (!(xtensa = kzalloc(sizeof(*xtensa), GFP_KERNEL)))
		return -ENOMEM;
	xtensa->func = func;
	xtensa->addr = addr;
	*pengine = &xtensa->engine;

	return nvkm_engine_ctor(&nvkm_xtensa, device, index, func->pmc_enable,
				enable, &xtensa->engine);
}
