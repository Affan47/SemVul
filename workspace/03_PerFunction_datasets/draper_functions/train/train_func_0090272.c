drxdap_fasi_read_reg32(struct i2c_device_addr *dev_addr,
					 u32 addr,
					 u32 *data, u32 flags)
{
	u8 buf[sizeof(*data)];
	int rc;

	if (!data)
		return -EINVAL;

	rc = drxdap_fasi_read_block(dev_addr, addr, sizeof(*data), buf, flags);
	*data = (((u32) buf[0]) << 0) +
	    (((u32) buf[1]) << 8) +
	    (((u32) buf[2]) << 16) + (((u32) buf[3]) << 24);
	return rc;
}
