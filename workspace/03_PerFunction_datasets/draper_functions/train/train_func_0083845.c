umt_mt352_frontend_attach(struct dvb_usb_adapter *adap)
{
	struct mt352_config umt_config;

	memset(&umt_config,0,sizeof(struct mt352_config));
	umt_config.demod_init = umt_mt352_demod_init;
	umt_config.demod_address = 0xf;

	adap->fe_adap[0].fe = dvb_attach(mt352_attach, &umt_config, &adap->dev->i2c_adap);

	return 0;
}
