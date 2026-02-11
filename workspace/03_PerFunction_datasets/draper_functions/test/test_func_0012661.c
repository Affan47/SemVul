ds2482_send_cmd_data(struct ds2482_data *pdev,
				       u8 cmd, u8 byte)
{
	if (i2c_smbus_write_byte_data(pdev->client, cmd, byte) < 0)
		return -1;


	pdev->read_prt = (cmd != DS2482_CMD_WRITE_CONFIG) ?
			 DS2482_PTR_CODE_STATUS : DS2482_PTR_CODE_CONFIG;
	return 0;
}
