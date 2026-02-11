elan_i2c_write_fw_block(struct i2c_client *client,
				   const u8 *page, u16 checksum, int idx)
{
	struct device *dev = &client->dev;
	u8 page_store[ETP_FW_PAGE_SIZE + 4];
	u8 val[3];
	u16 result;
	int ret, error;

	page_store[0] = ETP_I2C_IAP_REG_L;
	page_store[1] = ETP_I2C_IAP_REG_H;
	memcpy(&page_store[2], page, ETP_FW_PAGE_SIZE);

	put_unaligned_le16(checksum, &page_store[ETP_FW_PAGE_SIZE + 2]);

	ret = i2c_master_send(client, page_store, sizeof(page_store));
	if (ret != sizeof(page_store)) {
		error = ret < 0 ? ret : -EIO;
		dev_err(dev, "Failed to write page %d: %d\n", idx, error);
		return error;
	}


	msleep(20);

	error = elan_i2c_read_cmd(client, ETP_I2C_IAP_CTRL_CMD, val);
	if (error) {
		dev_err(dev, "Failed to read IAP write result: %d\n", error);
		return error;
	}

	result = le16_to_cpup((__le16 *)val);
	if (result & (ETP_FW_IAP_PAGE_ERR | ETP_FW_IAP_INTF_ERR)) {
		dev_err(dev, "IAP reports failed write: %04hx\n",
			result);
		return -EIO;
	}

	return 0;
}
