sis5595_access(struct i2c_adapter *adap, u16 addr,
			  unsigned short flags, char read_write,
			  u8 command, int size, union i2c_smbus_data *data)
{
	int status;

	switch (size) {
	case I2C_SMBUS_QUICK:
		sis5595_write(SMB_ADDR, ((addr & 0x7f) << 1) | (read_write & 0x01));
		size = SIS5595_QUICK;
		break;
	case I2C_SMBUS_BYTE:
		sis5595_write(SMB_ADDR, ((addr & 0x7f) << 1) | (read_write & 0x01));
		if (read_write == I2C_SMBUS_WRITE)
			sis5595_write(SMB_CMD, command);
		size = SIS5595_BYTE;
		break;
	case I2C_SMBUS_BYTE_DATA:
		sis5595_write(SMB_ADDR, ((addr & 0x7f) << 1) | (read_write & 0x01));
		sis5595_write(SMB_CMD, command);
		if (read_write == I2C_SMBUS_WRITE)
			sis5595_write(SMB_BYTE, data->byte);
		size = SIS5595_BYTE_DATA;
		break;
	case I2C_SMBUS_PROC_CALL:
	case I2C_SMBUS_WORD_DATA:
		sis5595_write(SMB_ADDR, ((addr & 0x7f) << 1) | (read_write & 0x01));
		sis5595_write(SMB_CMD, command);
		if (read_write == I2C_SMBUS_WRITE) {
			sis5595_write(SMB_BYTE, data->word & 0xff);
			sis5595_write(SMB_BYTE + 1,
				      (data->word & 0xff00) >> 8);
		}
		size = (size == I2C_SMBUS_PROC_CALL) ? SIS5595_PROC_CALL : SIS5595_WORD_DATA;
		break;
	default:
		dev_warn(&adap->dev, "Unsupported transaction %d\n", size);
		return -EOPNOTSUPP;
	}

	sis5595_write(SMB_CTL_LO, ((size & 0x0E)));

	status = sis5595_transaction(adap);
	if (status)
		return status;

	if ((size != SIS5595_PROC_CALL) &&
	    ((read_write == I2C_SMBUS_WRITE) || (size == SIS5595_QUICK)))
		return 0;


	switch (size) {
	case SIS5595_BYTE:
	case SIS5595_BYTE_DATA:
		data->byte = sis5595_read(SMB_BYTE);
		break;
	case SIS5595_WORD_DATA:
	case SIS5595_PROC_CALL:
		data->word = sis5595_read(SMB_BYTE) + (sis5595_read(SMB_BYTE + 1) << 8);
		break;
	}
	return 0;
}
