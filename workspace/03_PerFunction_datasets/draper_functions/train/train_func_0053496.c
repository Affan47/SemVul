tps65912_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct tps65912 *tps65912;

	tps65912 = devm_kzalloc(&i2c->dev,
				sizeof(struct tps65912), GFP_KERNEL);
	if (tps65912 == NULL)
		return -ENOMEM;

	i2c_set_clientdata(i2c, tps65912);
	tps65912->dev = &i2c->dev;
	tps65912->control_data = i2c;
	tps65912->read = tps65912_i2c_read;
	tps65912->write = tps65912_i2c_write;

	return tps65912_device_init(tps65912);
}
