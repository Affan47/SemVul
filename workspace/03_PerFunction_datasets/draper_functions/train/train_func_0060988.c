nes_read_1G_phy_reg(struct nes_device *nesdev, u8 phy_reg, u8 phy_addr, u16 *data)
{
	u32 u32temp;
	u32 counter;


	nes_write_indexed(nesdev, NES_IDX_MAC_MDIO_CONTROL,
			0x60020000 | ((u32)phy_reg << 18) | ((u32)phy_addr << 23));
	for (counter = 0; counter < 100 ; counter++) {
		udelay(30);
		u32temp = nes_read_indexed(nesdev, NES_IDX_MAC_INT_STATUS);
		if (u32temp & 1) {

			nes_write_indexed(nesdev, NES_IDX_MAC_INT_STATUS, 1);
			break;
		}
	}
	if (!(u32temp & 1)) {
		nes_debug(NES_DBG_PHY, "Phy is not responding. interrupt status = 0x%X.\n",
				u32temp);
		*data = 0xffff;
	} else {
		*data = (u16)nes_read_indexed(nesdev, NES_IDX_MAC_MDIO_CONTROL);
	}
}
