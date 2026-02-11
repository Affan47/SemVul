viafb_lvds_identify_vt1636(u8 i2c_adapter)
{
	u8 Buffer[2];

	DEBUG_MSG(KERN_INFO "viafb_lvds_identify_vt1636.\n");


	viaparinfo->chip_info->lvds_chip_info.lvds_chip_slave_addr =
		VT1636_LVDS_I2C_ADDR;


	if (viafb_i2c_readbyte(i2c_adapter, VT1636_LVDS_I2C_ADDR,
					0x00, &Buffer[0]))
		return false;
	viafb_i2c_readbyte(i2c_adapter, VT1636_LVDS_I2C_ADDR, 0x01, &Buffer[1]);

	if (!((Buffer[0] == 0x06) && (Buffer[1] == 0x11)))
		return false;


	viafb_i2c_readbyte(i2c_adapter, VT1636_LVDS_I2C_ADDR, 0x02, &Buffer[0]);
	viafb_i2c_readbyte(i2c_adapter, VT1636_LVDS_I2C_ADDR, 0x03, &Buffer[1]);
	if ((Buffer[0] == 0x45) && (Buffer[1] == 0x33)) {
		viaparinfo->chip_info->lvds_chip_info.lvds_chip_name =
			VT1636_LVDS;
		return true;
	}

	return false;
}
