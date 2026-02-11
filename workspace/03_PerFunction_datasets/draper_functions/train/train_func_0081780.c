soc_camera_i2c_free(struct soc_camera_device *icd)
{
	struct i2c_client *client =
		to_i2c_client(to_soc_camera_control(icd));
	struct i2c_adapter *adap;
	struct soc_camera_subdev_desc *ssdd;

	icd->control = NULL;
	if (icd->sasc)
		return;

	adap = client->adapter;
	ssdd = client->dev.platform_data;
	v4l2_device_unregister_subdev(i2c_get_clientdata(client));
	i2c_unregister_device(client);
	i2c_put_adapter(adap);
	kfree(ssdd);
	v4l2_clk_unregister(icd->clk);
	icd->clk = NULL;
}
