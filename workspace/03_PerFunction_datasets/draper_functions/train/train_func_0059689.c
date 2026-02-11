gf100_gr_ctor_fw(struct gf100_gr *gr, const char *fwname,
		 struct gf100_gr_fuc *fuc)
{
	struct nvkm_subdev *subdev = &gr->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	const struct firmware *fw;
	char f[64];
	char cname[16];
	int ret;
	int i;


	strncpy(cname, device->chip->name, sizeof(cname));
	cname[sizeof(cname) - 1] = '\0';
	i = strlen(cname);
	while (i) {
		--i;
		cname[i] = tolower(cname[i]);
	}

	snprintf(f, sizeof(f), "nvidia/%s/%s.bin", cname, fwname);
	ret = request_firmware(&fw, f, device->dev);
	if (ret) {
		nvkm_error(subdev, "failed to load %s\n", fwname);
		return ret;
	}

	fuc->size = fw->size;
	fuc->data = kmemdup(fw->data, fuc->size, GFP_KERNEL);
	release_firmware(fw);
	return (fuc->data != NULL) ? 0 : -ENOMEM;
}
