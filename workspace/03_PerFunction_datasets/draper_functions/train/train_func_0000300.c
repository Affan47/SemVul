tea5764_i2c_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	struct tea5764_device *radio;
	struct v4l2_device *v4l2_dev;
	struct v4l2_ctrl_handler *hdl;
	struct tea5764_regs *r;
	int ret;

	PDEBUG("probe");
	radio = kzalloc(sizeof(struct tea5764_device), GFP_KERNEL);
	if (!radio)
		return -ENOMEM;

	v4l2_dev = &radio->v4l2_dev;
	ret = v4l2_device_register(&client->dev, v4l2_dev);
	if (ret < 0) {
		v4l2_err(v4l2_dev, "could not register v4l2_device\n");
		goto errfr;
	}

	hdl = &radio->ctrl_handler;
	v4l2_ctrl_handler_init(hdl, 1);
	v4l2_ctrl_new_std(hdl, &tea5764_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	v4l2_dev->ctrl_handler = hdl;
	if (hdl->error) {
		ret = hdl->error;
		v4l2_err(v4l2_dev, "Could not register controls\n");
		goto errunreg;
	}

	mutex_init(&radio->mutex);
	radio->i2c_client = client;
	ret = tea5764_i2c_read(radio);
	if (ret)
		goto errunreg;
	r = &radio->regs;
	PDEBUG("chipid = %04X, manid = %04X", r->chipid, r->manid);
	if (r->chipid != TEA5764_CHIPID ||
		(r->manid & 0x0fff) != TEA5764_MANID) {
		PWARN("This chip is not a TEA5764!");
		ret = -EINVAL;
		goto errunreg;
	}

	radio->vdev = tea5764_radio_template;

	i2c_set_clientdata(client, radio);
	video_set_drvdata(&radio->vdev, radio);
	radio->vdev.lock = &radio->mutex;
	radio->vdev.v4l2_dev = v4l2_dev;


	tea5764_i2c_read(radio);
	tea5764_set_audout_mode(radio, V4L2_TUNER_MODE_STEREO);
	tea5764_mute(radio, 1);
	tea5764_power_down(radio);

	ret = video_register_device(&radio->vdev, VFL_TYPE_RADIO, radio_nr);
	if (ret < 0) {
		PWARN("Could not register video device!");
		goto errunreg;
	}

	PINFO("registered.");
	return 0;
errunreg:
	v4l2_ctrl_handler_free(hdl);
	v4l2_device_unregister(v4l2_dev);
errfr:
	kfree(radio);
	return ret;
}
