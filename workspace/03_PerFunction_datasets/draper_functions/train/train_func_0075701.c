flexcop_device_kmalloc(size_t bus_specific_len)
{
	void *bus;
	struct flexcop_device *fc = kzalloc(sizeof(struct flexcop_device),
				GFP_KERNEL);
	if (!fc) {
		err("no memory");
		return NULL;
	}

	bus = kzalloc(bus_specific_len, GFP_KERNEL);
	if (!bus) {
		err("no memory");
		kfree(fc);
		return NULL;
	}

	fc->bus_specific = bus;

	return fc;
}
