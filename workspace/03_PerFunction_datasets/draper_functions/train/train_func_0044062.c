Devices_Frame(void)
{
	if (Devices_enable_h_patch)
		h_entry_address = Devices_UpdateHATABSEntry('H', h_entry_address, H_TABLE_ADDRESS);

#ifdef R_IO_DEVICE
	if (Devices_enable_r_patch)
		r_entry_address = Devices_UpdateHATABSEntry('R', r_entry_address, R_TABLE_ADDRESS);
#endif

	if (Devices_enable_b_patch)
		b_entry_address = Devices_UpdateHATABSEntry('B', b_entry_address, B_TABLE_ADDRESS);
}
