rtw_hal_read_rfreg(struct adapter *adapt, enum rf_radio_path rfpath,
		       u32 regaddr, u32 bitmask)
{
	u32 data = 0;

	if (adapt->HalFunc.read_rfreg)
		data = adapt->HalFunc.read_rfreg(adapt, rfpath, regaddr,
						    bitmask);
	return data;
}
