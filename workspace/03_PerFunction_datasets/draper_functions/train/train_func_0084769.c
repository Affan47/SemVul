i2c_nuvoton_recv_data(struct i2c_client *client,
				 struct tpm_chip *chip, u8 *buf, size_t count)
{
	s32 rc;
	int burst_count, bytes2read, size = 0;

	while (size < count &&
	       i2c_nuvoton_wait_for_data_avail(chip,
					       chip->vendor.timeout_c,
					       &chip->vendor.read_queue) == 0) {
		burst_count = i2c_nuvoton_get_burstcount(client, chip);
		if (burst_count < 0) {
			dev_err(&chip->dev,
				"%s() fail to read burstCount=%d\n", __func__,
				burst_count);
			return -EIO;
		}
		bytes2read = min_t(size_t, burst_count, count - size);
		rc = i2c_nuvoton_read_buf(client, TPM_DATA_FIFO_R,
					  bytes2read, &buf[size]);
		if (rc < 0) {
			dev_err(&chip->dev,
				"%s() fail on i2c_nuvoton_read_buf()=%d\n",
				__func__, rc);
			return -EIO;
		}
		dev_dbg(&chip->dev, "%s(%d):", __func__, bytes2read);
		size += bytes2read;
	}

	return size;
}
