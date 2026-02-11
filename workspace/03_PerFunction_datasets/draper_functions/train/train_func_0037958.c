nvkm_disp_new_(const struct nvkm_disp_func *func, struct nvkm_device *device,
	       int index, int heads, struct nvkm_disp **pdisp)
{
	if (!(*pdisp = kzalloc(sizeof(**pdisp), GFP_KERNEL)))
		return -ENOMEM;
	return nvkm_disp_ctor(func, device, index, heads, *pdisp);
}
