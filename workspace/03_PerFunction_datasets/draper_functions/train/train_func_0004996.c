i2c_hid_get_input(struct i2c_hid *ihid)
{
	int ret, ret_size;
	int size = le16_to_cpu(ihid->hdesc.wMaxInputLength);

	if (size > ihid->bufsize)
		size = ihid->bufsize;

	ret = i2c_master_recv(ihid->client, ihid->inbuf, size);
	if (ret != size) {
		if (ret < 0)
			return;

		dev_err(&ihid->client->dev, "%s: got %d data instead of %d\n",
			__func__, ret, size);
		return;
	}

	ret_size = ihid->inbuf[0] | ihid->inbuf[1] << 8;

	if (!ret_size) {

		if (test_and_clear_bit(I2C_HID_RESET_PENDING, &ihid->flags))
			wake_up(&ihid->wait);
		return;
	}

	if (ret_size > size) {
		dev_err(&ihid->client->dev, "%s: incomplete report (%d/%d)\n",
			__func__, size, ret_size);
		return;
	}

	i2c_hid_dbg(ihid, "input: %*ph\n", ret_size, ihid->inbuf);

	if (test_bit(I2C_HID_STARTED, &ihid->flags))
		hid_input_report(ihid->hid, HID_INPUT_REPORT, ihid->inbuf + 2,
				ret_size - 2, 1);

	return;
}
