wl1273_core_probe(struct i2c_client *client,
				       const struct i2c_device_id *id)
{
	struct wl1273_fm_platform_data *pdata = dev_get_platdata(&client->dev);
	struct wl1273_core *core;
	struct mfd_cell *cell;
	int children = 0;
	int r = 0;

	dev_dbg(&client->dev, "%s\n", __func__);

	if (!pdata) {
		dev_err(&client->dev, "No platform data.\n");
		return -EINVAL;
	}

	if (!(pdata->children & WL1273_RADIO_CHILD)) {
		dev_err(&client->dev, "Cannot function without radio child.\n");
		return -EINVAL;
	}

	core = devm_kzalloc(&client->dev, sizeof(*core), GFP_KERNEL);
	if (!core)
		return -ENOMEM;

	core->pdata = pdata;
	core->client = client;
	mutex_init(&core->lock);

	i2c_set_clientdata(client, core);

	dev_dbg(&client->dev, "%s: Have V4L2.\n", __func__);

	cell = &core->cells[children];
	cell->name = "wl1273_fm_radio";
	cell->platform_data = &core;
	cell->pdata_size = sizeof(core);
	children++;

	core->read = wl1273_fm_read_reg;
	core->write = wl1273_fm_write_cmd;
	core->write_data = wl1273_fm_write_data;
	core->set_audio = wl1273_fm_set_audio;
	core->set_volume = wl1273_fm_set_volume;

	if (pdata->children & WL1273_CODEC_CHILD) {
		cell = &core->cells[children];

		dev_dbg(&client->dev, "%s: Have codec.\n", __func__);
		cell->name = "wl1273-codec";
		cell->platform_data = &core;
		cell->pdata_size = sizeof(core);
		children++;
	}

	dev_dbg(&client->dev, "%s: number of children: %d.\n",
		__func__, children);

	r = mfd_add_devices(&client->dev, -1, core->cells,
			    children, NULL, 0, NULL);
	if (r)
		goto err;

	return 0;

err:
	pdata->free_resources();

	dev_dbg(&client->dev, "%s\n", __func__);

	return r;
}
