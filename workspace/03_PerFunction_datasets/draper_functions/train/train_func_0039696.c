otp_read(struct spi_device *spi, unsigned base,
		uint8_t *buf, loff_t off, size_t len)
{
	struct spi_message	m;
	size_t			l;
	uint8_t			*scratch;
	struct spi_transfer	t;
	int			status;

	if (off > 64)
		return -EINVAL;

	if ((off + len) > 64)
		len = 64 - off;

	spi_message_init(&m);

	l = 4 + base + off + len;
	scratch = kzalloc(l, GFP_KERNEL);
	if (!scratch)
		return -ENOMEM;


	scratch[0] = OP_READ_SECURITY;

	memset(&t, 0, sizeof t);
	t.tx_buf = scratch;
	t.rx_buf = scratch;
	t.len = l;
	spi_message_add_tail(&t, &m);

	dataflash_waitready(spi);

	status = spi_sync(spi, &m);
	if (status >= 0) {
		memcpy(buf, scratch + 4 + base + off, len);
		status = len;
	}

	kfree(scratch);
	return status;
}
