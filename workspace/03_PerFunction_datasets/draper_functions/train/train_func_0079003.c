i2c_atmel_recv(struct tpm_chip *chip, u8 *buf, size_t count)
{
	struct priv_data *priv = chip->vendor.priv;
	struct i2c_client *client = to_i2c_client(chip->dev.parent);
	struct tpm_output_header *hdr =
		(struct tpm_output_header *)priv->buffer;
	u32 expected_len;
	int rc;

	if (priv->len == 0)
		return -EIO;


	expected_len = be32_to_cpu(hdr->length);
	if (expected_len > count)
		return -ENOMEM;

	if (priv->len >= expected_len) {
		dev_dbg(&chip->dev,
			"%s early(buf=%*ph count=%0zx) -> ret=%d\n", __func__,
			(int)min_t(size_t, 64, expected_len), buf, count,
			expected_len);
		memcpy(buf, priv->buffer, expected_len);
		return expected_len;
	}

	rc = i2c_master_recv(client, buf, expected_len);
	dev_dbg(&chip->dev,
		"%s reread(buf=%*ph count=%0zx) -> ret=%d\n", __func__,
		(int)min_t(size_t, 64, expected_len), buf, count,
		expected_len);
	return rc;
}
