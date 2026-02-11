nv50_disp_new_(const struct nv50_disp_func *func, struct nvkm_device *device,
	       int index, int heads, struct nvkm_disp **pdisp)
{
	struct nv50_disp *disp;
	int ret;

	if (!(disp = kzalloc(sizeof(*disp), GFP_KERNEL)))
		return -ENOMEM;
	INIT_WORK(&disp->supervisor, func->super);
	disp->func = func;
	*pdisp = &disp->base;

	ret = nvkm_disp_ctor(&nv50_disp_, device, index, heads, &disp->base);
	if (ret)
		return ret;

	return nvkm_event_init(func->uevent, 1, 1 + (heads * 4), &disp->uevent);
}
