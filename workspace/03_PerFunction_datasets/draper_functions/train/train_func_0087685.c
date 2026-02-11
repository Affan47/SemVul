select_core_and_segment(struct ssb_device *dev,
				   u16 *offset)
{
	struct ssb_bus *bus = dev->bus;
	int err;
	u8 need_segment;

	if (*offset >= 0x800) {
		*offset -= 0x800;
		need_segment = 1;
	} else
		need_segment = 0;

	if (unlikely(dev != bus->mapped_device)) {
		err = ssb_pcmcia_switch_core(bus, dev);
		if (unlikely(err))
			return err;
	}
	if (unlikely(need_segment != bus->mapped_pcmcia_seg)) {
		err = ssb_pcmcia_switch_segment(bus, need_segment);
		if (unlikely(err))
			return err;
	}

	return 0;
}
