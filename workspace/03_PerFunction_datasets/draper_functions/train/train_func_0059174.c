cx231xx_config_tuner(struct cx231xx *dev)
{
	struct tuner_setup tun_setup;
	struct v4l2_frequency f;

	if (dev->tuner_type == TUNER_ABSENT)
		return;

	tun_setup.mode_mask = T_ANALOG_TV | T_RADIO;
	tun_setup.type = dev->tuner_type;
	tun_setup.addr = dev->tuner_addr;
	tun_setup.tuner_callback = cx231xx_tuner_callback;

	tuner_call(dev, tuner, s_type_addr, &tun_setup);

#if 0
	if (tun_setup.type == TUNER_XC5000) {
		static struct xc2028_ctrl ctrl = {
			.fname = XC5000_DEFAULT_FIRMWARE,
			.max_len = 64,
			.demod = 0;
		};
		struct v4l2_priv_tun_config cfg = {
			.tuner = dev->tuner_type,
			.priv = &ctrl,
		};
		tuner_call(dev, tuner, s_config, &cfg);
	}
#endif

	f.tuner = 0;
	f.type = V4L2_TUNER_ANALOG_TV;
	f.frequency = 9076;
	dev->ctl_freq = f.frequency;
	call_all(dev, tuner, s_frequency, &f);

}
