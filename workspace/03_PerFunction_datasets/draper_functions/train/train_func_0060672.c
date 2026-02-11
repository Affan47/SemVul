da9034_read_status(struct da903x_chip *chip, unsigned int *status)
{
	uint8_t v[2] = {0, 0};
	int ret = 0;

	ret = __da903x_reads(chip->client, DA9034_STATUS_A, 2, v);
	if (ret)
		return ret;

	*status = (v[1] << 8) | v[0];
	return 0;
}
