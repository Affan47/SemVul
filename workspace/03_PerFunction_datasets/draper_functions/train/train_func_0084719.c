nvbios_init(struct nvkm_subdev *subdev, bool execute)
{
	struct nvkm_bios *bios = subdev->device->bios;
	int ret = 0;
	int i = -1;
	u16 data;

	if (execute)
		nvkm_debug(subdev, "running init tables\n");
	while (!ret && (data = (init_script(bios, ++i)))) {
		struct nvbios_init init = {
			.subdev = subdev,
			.bios = bios,
			.offset = data,
			.outp = NULL,
			.crtc = -1,
			.execute = execute ? 1 : 0,
		};

		ret = nvbios_exec(&init);
	}


	if (!ret && (data = init_unknown_script(bios))) {
		struct nvbios_init init = {
			.subdev = subdev,
			.bios = bios,
			.offset = data,
			.outp = NULL,
			.crtc = -1,
			.execute = execute ? 1 : 0,
		};

		ret = nvbios_exec(&init);
	}

	return ret;
}
