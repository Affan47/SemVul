nvkm_voltgpio_get(struct nvkm_volt *volt)
{
	struct nvkm_gpio *gpio = volt->subdev.device->gpio;
	u8 vid = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(tags); i++) {
		if (volt->vid_mask & (1 << i)) {
			int ret = nvkm_gpio_get(gpio, 0, tags[i], 0xff);
			if (ret < 0)
				return ret;
			vid |= ret << i;
		}
	}

	return vid;
}
