mcb_get_irq(struct mcb_device *dev)
{
	struct mcb_bus *bus = dev->bus;

	if (bus->get_irq)
		return bus->get_irq(dev);

	return __mcb_get_irq(dev);
}
