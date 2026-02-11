ov2659_set_frame_size(struct ov2659 *ov2659)
{
	struct i2c_client *client = ov2659->client;

	dev_dbg(&client->dev, "%s\n", __func__);

	return ov2659_write_array(ov2659->client, ov2659->frame_size->regs);
}
