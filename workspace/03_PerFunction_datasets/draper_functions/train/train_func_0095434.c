s5k6aa_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	const struct s5k6aa_platform_data *pdata = client->dev.platform_data;
	struct v4l2_subdev *sd;
	struct s5k6aa *s5k6aa;
	int i, ret;

	if (pdata == NULL) {
		dev_err(&client->dev, "Platform data not specified\n");
		return -EINVAL;
	}

	if (pdata->mclk_frequency == 0) {
		dev_err(&client->dev, "MCLK frequency not specified\n");
		return -EINVAL;
	}

	s5k6aa = devm_kzalloc(&client->dev, sizeof(*s5k6aa), GFP_KERNEL);
	if (!s5k6aa)
		return -ENOMEM;

	mutex_init(&s5k6aa->lock);

	s5k6aa->mclk_frequency = pdata->mclk_frequency;
	s5k6aa->bus_type = pdata->bus_type;
	s5k6aa->mipi_lanes = pdata->nlanes;
	s5k6aa->s_power	= pdata->set_power;
	s5k6aa->inv_hflip = pdata->horiz_flip;
	s5k6aa->inv_vflip = pdata->vert_flip;

	sd = &s5k6aa->sd;
	v4l2_i2c_subdev_init(sd, client, &s5k6aa_subdev_ops);
	strlcpy(sd->name, DRIVER_NAME, sizeof(sd->name));

	sd->internal_ops = &s5k6aa_subdev_internal_ops;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	s5k6aa->pad.flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.type = MEDIA_ENT_T_V4L2_SUBDEV_SENSOR;
	ret = media_entity_init(&sd->entity, 1, &s5k6aa->pad, 0);
	if (ret)
		return ret;

	ret = s5k6aa_configure_gpios(s5k6aa, pdata);
	if (ret)
		goto out_err;

	for (i = 0; i < S5K6AA_NUM_SUPPLIES; i++)
		s5k6aa->supplies[i].supply = s5k6aa_supply_names[i];

	ret = devm_regulator_bulk_get(&client->dev, S5K6AA_NUM_SUPPLIES,
				 s5k6aa->supplies);
	if (ret) {
		dev_err(&client->dev, "Failed to get regulators\n");
		goto out_err;
	}

	ret = s5k6aa_initialize_ctrls(s5k6aa);
	if (ret)
		goto out_err;

	s5k6aa_presets_data_init(s5k6aa);

	s5k6aa->ccd_rect.width = S5K6AA_WIN_WIDTH_MAX;
	s5k6aa->ccd_rect.height	= S5K6AA_WIN_HEIGHT_MAX;
	s5k6aa->ccd_rect.left = 0;
	s5k6aa->ccd_rect.top = 0;

	return 0;

out_err:
	media_entity_cleanup(&s5k6aa->sd.entity);
	return ret;
}
