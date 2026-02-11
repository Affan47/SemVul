si2157_stat_work(struct work_struct *work)
{
	struct si2157_dev *dev = container_of(work, struct si2157_dev, stat_work.work);
	struct dvb_frontend *fe = dev->fe;
	struct i2c_client *client = fe->tuner_priv;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	struct si2157_cmd cmd;
	int ret;

	dev_dbg(&client->dev, "\n");

	memcpy(cmd.args, "\x42\x00", 2);
	cmd.wlen = 2;
	cmd.rlen = 12;
	ret = si2157_cmd_execute(client, &cmd);
	if (ret)
		goto err;

	c->strength.stat[0].scale = FE_SCALE_DECIBEL;
	c->strength.stat[0].svalue = (s8) cmd.args[3] * 1000;

	schedule_delayed_work(&dev->stat_work, msecs_to_jiffies(2000));
	return;
err:
	c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	dev_dbg(&client->dev, "failed=%d\n", ret);
}
