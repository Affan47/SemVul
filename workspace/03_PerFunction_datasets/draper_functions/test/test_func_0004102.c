s3fb_ddc_setsda(void *data, int val)
{
	struct s3fb_info *par = data;
	unsigned char reg;

	reg = s3fb_ddc_read(par) | DDC_DRIVE_EN;
	if (val)
		reg |= DDC_SDA_OUT;
	else
		reg &= ~DDC_SDA_OUT;
	s3fb_ddc_write(par, reg);
}
