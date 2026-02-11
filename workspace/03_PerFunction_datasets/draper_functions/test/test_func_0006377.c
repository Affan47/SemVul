phy_set_rf_reg(struct adapter *adapt, enum rf_radio_path rf_path,
		     u32 reg_addr, u32 bit_mask, u32 data)
{
	u32 original_value, bit_shift;


	if (bit_mask != bRFRegOffsetMask) {
		original_value = rf_serial_read(adapt, rf_path, reg_addr);
		bit_shift =  cal_bit_shift(bit_mask);
		data = (original_value & (~bit_mask)) | (data << bit_shift);
	}

	rf_serial_write(adapt, rf_path, reg_addr, data);
}
