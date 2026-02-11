rtl28xxu_frontend_detach(struct dvb_usb_adapter *adap)
{
	struct dvb_usb_device *d = adap_to_d(adap);
	struct rtl28xxu_dev *dev = d_to_priv(d);
	struct i2c_client *client;

	dev_dbg(&d->intf->dev, "\n");


	client = dev->i2c_client_slave_demod;
	if (client) {
		module_put(client->dev.driver->owner);
		i2c_unregister_device(client);
	}


	client = dev->i2c_client_demod;
	if (client) {
		module_put(client->dev.driver->owner);
		i2c_unregister_device(client);
	}

	return 0;
}
