gf119_therm_init(struct nvkm_therm *therm)
{
	struct nvkm_device *device = therm->subdev.device;

	g84_sensor_setup(therm);


	nvkm_mask(device, 0x00e720, 0x00000003, 0x00000002);
	if (therm->fan->tach.func != DCB_GPIO_UNUSED) {
		nvkm_mask(device, 0x00d79c, 0x000000ff, therm->fan->tach.line);
		nvkm_wr32(device, 0x00e724, device->crystal * 1000);
		nvkm_mask(device, 0x00e720, 0x00000001, 0x00000001);
	}
	nvkm_mask(device, 0x00e720, 0x00000002, 0x00000000);
}
