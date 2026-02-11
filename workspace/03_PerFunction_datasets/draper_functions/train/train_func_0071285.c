go7007_register_encoder(struct go7007 *go, unsigned num_i2c_devs)
{
	int i, ret;

	dev_info(go->dev, "go7007: registering new %s\n", go->name);

	go->v4l2_dev.release = go7007_remove;
	ret = v4l2_device_register(go->dev, &go->v4l2_dev);
	if (ret < 0)
		return ret;

	mutex_lock(&go->hw_lock);
	ret = go7007_init_encoder(go);
	mutex_unlock(&go->hw_lock);
	if (ret < 0)
		return ret;

	ret = go7007_v4l2_ctrl_init(go);
	if (ret < 0)
		return ret;

	if (!go->i2c_adapter_online &&
			go->board_info->flags & GO7007_BOARD_USE_ONBOARD_I2C) {
		ret = go7007_i2c_init(go);
		if (ret < 0)
			return ret;
		go->i2c_adapter_online = 1;
	}
	if (go->i2c_adapter_online) {
		if (go->board_id == GO7007_BOARDID_ADS_USBAV_709) {

			go7007_write_addr(go, 0x3c82, 0x0009);
			msleep(50);
			go7007_write_addr(go, 0x3c82, 0x000d);
		}
		for (i = 0; i < num_i2c_devs; ++i)
			init_i2c_module(&go->i2c_adapter, &go->board_info->i2c_devs[i]);

		if (go->tuner_type >= 0) {
			struct tuner_setup setup = {
				.addr = ADDR_UNSET,
				.type = go->tuner_type,
				.mode_mask = T_ANALOG_TV,
			};

			v4l2_device_call_all(&go->v4l2_dev, 0, tuner,
				s_type_addr, &setup);
		}
		if (go->board_id == GO7007_BOARDID_ADLINK_MPG24)
			v4l2_subdev_call(go->sd_video, video, s_routing,
					0, 0, go->channel_number + 1);
	}

	ret = go7007_v4l2_init(go);
	if (ret < 0)
		return ret;

	if (go->board_info->flags & GO7007_BOARD_HAS_AUDIO) {
		go->audio_enabled = 1;
		go7007_snd_init(go);
	}
	return 0;
}
