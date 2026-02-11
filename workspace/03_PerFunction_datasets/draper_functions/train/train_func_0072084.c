cyapa_i2c_pip_read(struct cyapa *cyapa, u8 *buf, size_t size)
{
	int ret;

	if (size == 0)
		return 0;

	if (!buf || size > CYAPA_REG_MAP_SIZE)
		return -EINVAL;

	ret = i2c_master_recv(cyapa->client, buf, size);

	if (ret != size)
		return (ret < 0) ? ret : -EIO;
	return size;
}
