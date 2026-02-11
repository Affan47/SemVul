cx23417_g_register(struct cx23885_dev *dev,
			      struct v4l2_dbg_register *reg)
{
	u32 value;

	if (dev->v4l_device == NULL)
		return -EINVAL;

	if ((reg->reg & 0x3) != 0 || reg->reg >= 0x10000)
		return -EINVAL;

	if (mc417_register_read(dev, (u16) reg->reg, &value))
		return -EINVAL;

	reg->size = 4;
	reg->val = value;
	return 0;
}
