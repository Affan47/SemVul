m920x_mt352_frontend_attach_vp7049(struct dvb_usb_adapter *adap)
{
	struct m920x_inits vp7049_fe_init_seq[] = {


		{ 0xff28,         0x00 },
		{ 0xff23,         0x00 },
		{ 0xff28,         0x00 },
		{ 0xff23,         0x00 },
		{ 0xff21,         0x20 },
		{ 0xff21,         0x60 },
		{ 0xff28,         0x00 },
		{ 0xff22,         0x00 },
		{ 0xff20,         0x30 },
		{ 0xff20,         0x20 },
		{ 0xff20,         0x30 },
		{ }
	};
	int ret;

	deb("%s\n", __func__);

	ret = m920x_write_seq(adap->dev->udev, M9206_CORE, vp7049_fe_init_seq);
	if (ret != 0) {
		deb("Initialization of vp7049 frontend failed.");
		return ret;
	}

	return m920x_mt352_frontend_attach(adap);
}
