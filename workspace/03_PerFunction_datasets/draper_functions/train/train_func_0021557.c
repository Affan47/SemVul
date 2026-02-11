nv50_devinit_preinit(struct nvkm_devinit *base)
{
	struct nv50_devinit *init = nv50_devinit(base);
	struct nvkm_subdev *subdev = &init->base.subdev;
	struct nvkm_device *device = subdev->device;


	if (!init->base.post) {
		u64 disable = nvkm_devinit_disable(&init->base);
		if (disable & (1ULL << NVKM_ENGINE_DISP))
			init->base.post = true;
	}


	if (!init->base.post) {
		if (!nvkm_rdvgac(device, 0, 0x00) &&
		    !nvkm_rdvgac(device, 0, 0x1a)) {
			nvkm_debug(subdev, "adaptor not initialised\n");
			init->base.post = true;
		}
	}
}
