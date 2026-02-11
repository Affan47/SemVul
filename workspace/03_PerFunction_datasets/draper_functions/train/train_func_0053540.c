si4713_remove(struct i2c_client *client)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(client);
	struct si4713_device *sdev = to_si4713_device(sd);

	platform_device_unregister(sdev->pd);

	if (sdev->power_state)
		si4713_set_power_state(sdev, POWER_DOWN);

	v4l2_device_unregister_subdev(sd);
	v4l2_ctrl_handler_free(sd->ctrl_handler);

	return 0;
}
