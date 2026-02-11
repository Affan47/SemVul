adis16136_get_freq(struct adis16136 *adis16136, unsigned int *freq)
{
	uint16_t t;
	int ret;

	ret = adis_read_reg_16(&adis16136->adis, ADIS16136_REG_SMPL_PRD, &t);
	if (ret < 0)
		return ret;

	*freq = 32768 / (t + 1);

	return 0;
}
