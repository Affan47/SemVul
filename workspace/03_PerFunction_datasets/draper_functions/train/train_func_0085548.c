tps65010_config_vdcdc2(unsigned value)
{
	struct i2c_client *c;
	int	 status;

	if (!the_tps)
		return -ENODEV;

	c = the_tps->client;
	mutex_lock(&the_tps->lock);

	pr_debug("%s: vdcdc2 0x%02x\n", DRIVER_NAME,
		 i2c_smbus_read_byte_data(c, TPS_VDCDC2));

	status = i2c_smbus_write_byte_data(c, TPS_VDCDC2, value);

	if (status != 0)
		printk(KERN_ERR "%s: Failed to write vdcdc2 register\n",
			DRIVER_NAME);
	else
		pr_debug("%s: vregs1 0x%02x\n", DRIVER_NAME,
			 i2c_smbus_read_byte_data(c, TPS_VDCDC2));

	mutex_unlock(&the_tps->lock);
	return status;
}
