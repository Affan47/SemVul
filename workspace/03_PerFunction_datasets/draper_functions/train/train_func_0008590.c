ssb_pcie_mdio_write(struct ssb_pcicore *pc, u8 device,
				u8 address, u16 data)
{
	const u16 mdio_control = 0x128;
	const u16 mdio_data = 0x12C;
	int max_retries = 10;
	u32 v;
	int i;

	v = 0x80;
	v |= 0x2;
	pcicore_write32(pc, mdio_control, v);

	if (pc->dev->id.revision >= 10) {
		max_retries = 200;
		ssb_pcie_mdio_set_phy(pc, device);
	}

	v = (1 << 30);
	v |= (1 << 28);
	v |= (1 << 17);
	if (pc->dev->id.revision < 10)
		v |= (u32)device << 22;
	v |= (u32)address << 18;
	v |= data;
	pcicore_write32(pc, mdio_data, v);

	udelay(10);
	for (i = 0; i < max_retries; i++) {
		v = pcicore_read32(pc, mdio_control);
		if (v & 0x100 )
			break;
		msleep(1);
	}
	pcicore_write32(pc, mdio_control, 0);
}
