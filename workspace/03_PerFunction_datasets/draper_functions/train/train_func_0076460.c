au0828_card_analog_fe_setup(struct au0828_dev *dev)
{
#ifdef CONFIG_VIDEO_AU0828_V4L2
	struct tuner_setup tun_setup;
	struct v4l2_subdev *sd;
	unsigned int mode_mask = T_ANALOG_TV;

	if (AUVI_INPUT(0).type != AU0828_VMUX_UNDEFINED) {


		sd = v4l2_i2c_new_subdev(&dev->v4l2_dev, &dev->i2c_adap,
				"au8522", 0x8e >> 1, NULL);
		if (sd == NULL)
			pr_err("analog subdev registration failed\n");
	}


	if (dev->board.tuner_type != TUNER_ABSENT && dev->board.has_analog) {

		sd = v4l2_i2c_new_subdev(&dev->v4l2_dev, &dev->i2c_adap,
				"tuner", dev->board.tuner_addr, NULL);
		if (sd == NULL)
			pr_err("tuner subdev registration fail\n");

		tun_setup.mode_mask      = mode_mask;
		tun_setup.type           = dev->board.tuner_type;
		tun_setup.addr           = dev->board.tuner_addr;
		tun_setup.tuner_callback = au0828_tuner_callback;
		v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, s_type_addr,
				     &tun_setup);
	}
#endif
}
