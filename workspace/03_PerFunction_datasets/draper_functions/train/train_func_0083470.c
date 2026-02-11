rt2500pci_link_stats(struct rt2x00_dev *rt2x00dev,
				 struct link_qual *qual)
{
	u32 reg;


	rt2x00mmio_register_read(rt2x00dev, CNT0, &reg);
	qual->rx_failed = rt2x00_get_field32(reg, CNT0_FCS_ERROR);


	rt2x00mmio_register_read(rt2x00dev, CNT3, &reg);
	qual->false_cca = rt2x00_get_field32(reg, CNT3_FALSE_CCA);
}
