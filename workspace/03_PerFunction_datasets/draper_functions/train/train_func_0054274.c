ssb_pci_write8(struct ssb_device *dev, u16 offset, u8 value)
{
	struct ssb_bus *bus = dev->bus;

	if (unlikely(ssb_pci_assert_buspower(bus)))
		return;
	if (unlikely(bus->mapped_device != dev)) {
		if (unlikely(ssb_pci_switch_core(bus, dev)))
			return;
	}
	iowrite8(value, bus->mmio + offset);
}
