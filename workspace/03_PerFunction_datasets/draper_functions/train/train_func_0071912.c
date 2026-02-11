macronix_quad_enable(struct spi_nor *nor)
{
	int ret, val;

	val = read_sr(nor);
	write_enable(nor);

	write_sr(nor, val | SR_QUAD_EN_MX);

	if (spi_nor_wait_till_ready(nor))
		return 1;

	ret = read_sr(nor);
	if (!(ret > 0 && (ret & SR_QUAD_EN_MX))) {
		dev_err(nor->dev, "Macronix Quad bit not set\n");
		return -EINVAL;
	}

	return 0;
}
