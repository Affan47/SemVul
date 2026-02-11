gk104_ram_train_init(struct nvkm_ram *ram)
{
	u8 ramcfg = nvbios_ramcfg_index(&ram->fb->subdev);
	struct gk104_ram_train *train;
	int ret, i;

	if (!(train = kzalloc(sizeof(*train), GFP_KERNEL)))
		return -ENOMEM;

	for (i = 0; i < 0x100; i++) {
		ret = gk104_ram_train_type(ram, i, ramcfg, train);
		if (ret && ret != -ENOENT)
			break;
	}

	switch (ram->type) {
	case NVKM_RAM_TYPE_GDDR5:
		ret = gk104_ram_train_init_0(ram, train);
		break;
	default:
		ret = 0;
		break;
	}

	kfree(train);
	return ret;
}
