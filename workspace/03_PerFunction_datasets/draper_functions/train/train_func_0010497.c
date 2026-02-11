ds2482_select_register(struct ds2482_data *pdev, u8 read_ptr)
{
	if (pdev->read_prt != read_ptr) {
		if (i2c_smbus_write_byte_data(pdev->client,
					      DS2482_CMD_SET_READ_PTR,
					      read_ptr) < 0)
			return -1;

		pdev->read_prt = read_ptr;
	}
	return 0;
}
