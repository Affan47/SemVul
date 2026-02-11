rt2400pci_config_filter(struct rt2x00_dev *rt2x00dev,
				    const unsigned int filter_flags)
{
	u32 reg;


	rt2x00mmio_register_read(rt2x00dev, RXCSR0, &reg);
	rt2x00_set_field32(&reg, RXCSR0_DROP_CRC,
			   !(filter_flags & FIF_FCSFAIL));
	rt2x00_set_field32(&reg, RXCSR0_DROP_PHYSICAL,
			   !(filter_flags & FIF_PLCPFAIL));
	rt2x00_set_field32(&reg, RXCSR0_DROP_CONTROL,
			   !(filter_flags & FIF_CONTROL));
	rt2x00_set_field32(&reg, RXCSR0_DROP_NOT_TO_ME, 1);
	rt2x00_set_field32(&reg, RXCSR0_DROP_TODS,
			   !rt2x00dev->intf_ap_count);
	rt2x00_set_field32(&reg, RXCSR0_DROP_VERSION_ERROR, 1);
	rt2x00mmio_register_write(rt2x00dev, RXCSR0, reg);
}
