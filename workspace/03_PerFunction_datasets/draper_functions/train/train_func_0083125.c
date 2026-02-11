spi_imx_clkdiv_1(unsigned int fin,
		unsigned int fspi, unsigned int max)
{
	int i;

	for (i = 2; i < max; i++)
		if (fspi * mxc_clkdivs[i] >= fin)
			return i;

	return max;
}
