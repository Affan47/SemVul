nv40_volt_new(struct nvkm_device *device, int index, struct nvkm_volt **pvolt)
{
	struct nvkm_volt *volt;
	int ret;

	ret = nvkm_volt_new_(&nv40_volt, device, index, &volt);
	*pvolt = volt;
	if (ret)
		return ret;

	return nvkm_voltgpio_init(volt);
}
