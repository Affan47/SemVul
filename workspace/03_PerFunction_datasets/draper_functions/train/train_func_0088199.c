matrox_w1_write_ddc_bit(void *data, u8 bit)
{
	u8 ret;
	struct matrox_device *dev = data;

	if (bit)
		bit = 0;
	else
		bit = dev->data_mask;

	ret = matrox_w1_read_reg(dev, MATROX_GET_CONTROL);
	matrox_w1_write_reg(dev, MATROX_GET_CONTROL, ((ret & ~dev->data_mask) | bit));
	matrox_w1_write_reg(dev, MATROX_GET_DATA, 0x00);
}
