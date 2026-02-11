ps8622_probe(struct i2c_client *client,
					const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct device_node *endpoint, *panel_node;
	struct ps8622_bridge *ps8622;
	int ret;

	ps8622 = devm_kzalloc(dev, sizeof(*ps8622), GFP_KERNEL);
	if (!ps8622)
		return -ENOMEM;

	endpoint = of_graph_get_next_endpoint(dev->of_node, NULL);
	if (endpoint) {
		panel_node = of_graph_get_remote_port_parent(endpoint);
		if (panel_node) {
			ps8622->panel = of_drm_find_panel(panel_node);
			of_node_put(panel_node);
			if (!ps8622->panel)
				return -EPROBE_DEFER;
		}
	}

	ps8622->client = client;

	ps8622->v12 = devm_regulator_get(dev, "vdd12");
	if (IS_ERR(ps8622->v12)) {
		dev_info(dev, "no 1.2v regulator found for PS8622\n");
		ps8622->v12 = NULL;
	}

	ps8622->gpio_slp = devm_gpiod_get(dev, "sleep", GPIOD_OUT_HIGH);
	if (IS_ERR(ps8622->gpio_slp)) {
		ret = PTR_ERR(ps8622->gpio_slp);
		dev_err(dev, "cannot get gpio_slp %d\n", ret);
		return ret;
	}


	ps8622->gpio_rst = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ps8622->gpio_rst)) {
		ret = PTR_ERR(ps8622->gpio_rst);
		dev_err(dev, "cannot get gpio_rst %d\n", ret);
		return ret;
	}

	ps8622->max_lane_count = id->driver_data;

	if (of_property_read_u32(dev->of_node, "lane-count",
						&ps8622->lane_count)) {
		ps8622->lane_count = ps8622->max_lane_count;
	} else if (ps8622->lane_count > ps8622->max_lane_count) {
		dev_info(dev, "lane-count property is too high,"
						"using max_lane_count\n");
		ps8622->lane_count = ps8622->max_lane_count;
	}

	if (!of_find_property(dev->of_node, "use-external-pwm", NULL)) {
		ps8622->bl = backlight_device_register("ps8622-backlight",
				dev, ps8622, &ps8622_backlight_ops,
				NULL);
		if (IS_ERR(ps8622->bl)) {
			DRM_ERROR("failed to register backlight\n");
			ret = PTR_ERR(ps8622->bl);
			ps8622->bl = NULL;
			return ret;
		}
		ps8622->bl->props.max_brightness = PS8622_MAX_BRIGHTNESS;
		ps8622->bl->props.brightness = PS8622_MAX_BRIGHTNESS;
	}

	ps8622->bridge.funcs = &ps8622_bridge_funcs;
	ps8622->bridge.of_node = dev->of_node;
	ret = drm_bridge_add(&ps8622->bridge);
	if (ret) {
		DRM_ERROR("Failed to add bridge\n");
		return ret;
	}

	i2c_set_clientdata(client, ps8622);

	return 0;
}
