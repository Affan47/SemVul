s2io_eeprom_test(struct s2io_nic *sp, uint64_t *data)
{
	int fail = 0;
	u64 ret_data, org_4F0, org_7F0;
	u8 saved_4F0 = 0, saved_7F0 = 0;
	struct net_device *dev = sp->dev;


	if (sp->device_type == XFRAME_I_DEVICE)
		if (!write_eeprom(sp, 0, 0, 3))
			fail = 1;


	if (!read_eeprom(sp, 0x4F0, &org_4F0))
		saved_4F0 = 1;
	if (!read_eeprom(sp, 0x7F0, &org_7F0))
		saved_7F0 = 1;


	if (write_eeprom(sp, 0x4F0, 0x012345, 3))
		fail = 1;
	if (read_eeprom(sp, 0x4F0, &ret_data))
		fail = 1;

	if (ret_data != 0x012345) {
		DBG_PRINT(ERR_DBG, "%s: eeprom test error at offset 0x4F0. "
			  "Data written %llx Data read %llx\n",
			  dev->name, (unsigned long long)0x12345,
			  (unsigned long long)ret_data);
		fail = 1;
	}


	write_eeprom(sp, 0x4F0, 0xFFFFFF, 3);


	if (sp->device_type == XFRAME_I_DEVICE)
		if (!write_eeprom(sp, 0x07C, 0, 3))
			fail = 1;


	if (write_eeprom(sp, 0x7F0, 0x012345, 3))
		fail = 1;
	if (read_eeprom(sp, 0x7F0, &ret_data))
		fail = 1;

	if (ret_data != 0x012345) {
		DBG_PRINT(ERR_DBG, "%s: eeprom test error at offset 0x7F0. "
			  "Data written %llx Data read %llx\n",
			  dev->name, (unsigned long long)0x12345,
			  (unsigned long long)ret_data);
		fail = 1;
	}


	write_eeprom(sp, 0x7F0, 0xFFFFFF, 3);

	if (sp->device_type == XFRAME_I_DEVICE) {

		if (!write_eeprom(sp, 0x080, 0, 3))
			fail = 1;


		if (!write_eeprom(sp, 0x0FC, 0, 3))
			fail = 1;


		if (!write_eeprom(sp, 0x100, 0, 3))
			fail = 1;


		if (!write_eeprom(sp, 0x4EC, 0, 3))
			fail = 1;
	}


	if (saved_4F0)
		write_eeprom(sp, 0x4F0, org_4F0, 3);
	if (saved_7F0)
		write_eeprom(sp, 0x7F0, org_7F0, 3);

	*data = fail;
	return fail;
}
