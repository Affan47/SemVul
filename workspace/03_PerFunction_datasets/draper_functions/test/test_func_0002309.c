si476x_core_regmap_writable_register(struct device *dev,
						 unsigned int reg)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct si476x_core *core = i2c_get_clientdata(client);

	return si476x_core_is_valid_property(core, (u16) reg) &&
		!si476x_core_is_readonly_property(core, (u16) reg);
}
