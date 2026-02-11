nv04_i2c_bus_new(struct nvkm_i2c_pad *pad, int id, u8 drive, u8 sense,
		 struct nvkm_i2c_bus **pbus)
{
	struct nv04_i2c_bus *bus;

	if (!(bus = kzalloc(sizeof(*bus), GFP_KERNEL)))
		return -ENOMEM;
	*pbus = &bus->base;

	nvkm_i2c_bus_ctor(&nv04_i2c_bus_func, pad, id, &bus->base);
	bus->drive = drive;
	bus->sense = sense;
	return 0;
}
