ipack_bus_register(struct device *parent, int slots,
					    const struct ipack_bus_ops *ops,
					    struct module *owner)
{
	int bus_nr;
	struct ipack_bus_device *bus;

	bus = kzalloc(sizeof(struct ipack_bus_device), GFP_KERNEL);
	if (!bus)
		return NULL;

	bus_nr = ida_simple_get(&ipack_ida, 0, 0, GFP_KERNEL);
	if (bus_nr < 0) {
		kfree(bus);
		return NULL;
	}

	bus->bus_nr = bus_nr;
	bus->parent = parent;
	bus->slots = slots;
	bus->ops = ops;
	bus->owner = owner;
	return bus;
}
