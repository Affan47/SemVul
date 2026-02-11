bttv_init_tuner(struct bttv *btv)
{
	int addr = ADDR_UNSET;

	if (ADDR_UNSET != bttv_tvcards[btv->c.type].tuner_addr)
		addr = bttv_tvcards[btv->c.type].tuner_addr;

	if (btv->tuner_type != TUNER_ABSENT) {
		struct tuner_setup tun_setup;


		if (btv->has_radio)
			v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
				&btv->c.i2c_adap, "tuner",
				0, v4l2_i2c_tuner_addrs(ADDRS_RADIO));
		v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
				&btv->c.i2c_adap, "tuner",
				0, v4l2_i2c_tuner_addrs(ADDRS_DEMOD));
		v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
				&btv->c.i2c_adap, "tuner",
				0, v4l2_i2c_tuner_addrs(ADDRS_TV_WITH_DEMOD));

		tun_setup.mode_mask = T_ANALOG_TV;
		tun_setup.type = btv->tuner_type;
		tun_setup.addr = addr;

		if (btv->has_radio)
			tun_setup.mode_mask |= T_RADIO;

		bttv_call_all(btv, tuner, s_type_addr, &tun_setup);
	}

	if (btv->tda9887_conf) {
		struct v4l2_priv_tun_config tda9887_cfg;

		tda9887_cfg.tuner = TUNER_TDA9887;
		tda9887_cfg.priv = &btv->tda9887_conf;

		bttv_call_all(btv, tuner, s_config, &tda9887_cfg);
	}
}
