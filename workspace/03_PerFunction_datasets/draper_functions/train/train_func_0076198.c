smiapp_registered(struct v4l2_subdev *subdev)
{
	struct smiapp_sensor *sensor = to_smiapp_sensor(subdev);
	struct i2c_client *client = v4l2_get_subdevdata(subdev);
	int rval;

	if (!client->dev.of_node) {
		rval = smiapp_init(sensor);
		if (rval)
			return rval;
	}

	rval = smiapp_register_subdevs(sensor);
	if (rval)
		smiapp_cleanup(sensor);

	return rval;
}
