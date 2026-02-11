ufx_lite_reset(struct ufx_data *dev)
{
	int status;
	u32 value;

	status = ufx_reg_write(dev, 0x3008, 0x00000001);
	check_warn_return(status, "ufx_lite_reset error writing 0x3008");

	status = ufx_reg_read(dev, 0x3008, &value);
	check_warn_return(status, "ufx_lite_reset error reading 0x3008");

	return (value == 0) ? 0 : -EIO;
}
