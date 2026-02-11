rt2500usb_rfkill_poll(struct rt2x00_dev *rt2x00dev)
{
	u16 reg;

	rt2500usb_register_read(rt2x00dev, MAC_CSR19, &reg);
	return rt2x00_get_field16(reg, MAC_CSR19_VAL7);
}
