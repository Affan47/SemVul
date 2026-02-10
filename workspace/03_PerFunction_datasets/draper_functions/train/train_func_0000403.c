em28xx_dvb_fini(struct em28xx *dev)
{
	struct em28xx_dvb *dvb;
	struct i2c_client *client;

	if (dev->is_audio_only) {

		return 0;
	}

	if (!dev->board.has_dvb) {

		return 0;
	}

	if (!dev->dvb)
		return 0;

	em28xx_info("Closing DVB extension\n");

	dvb = dev->dvb;

	em28xx_uninit_usb_xfer(dev, EM28XX_DIGITAL_MODE);

	if (dev->disconnected) {


		if (dvb->fe[0]) {
			prevent_sleep(&dvb->fe[0]->ops);
			dvb->fe[0]->exit = DVB_FE_DEVICE_REMOVED;
		}
		if (dvb->fe[1]) {
			prevent_sleep(&dvb->fe[1]->ops);
			dvb->fe[1]->exit = DVB_FE_DEVICE_REMOVED;
		}
	}


	client = dvb->i2c_client_sec;
	if (client) {
		module_put(client->dev.driver->owner);
		i2c_unregister_device(client);
	}


	client = dvb->i2c_client_tuner;
	if (client) {
		module_put(client->dev.driver->owner);
		i2c_unregister_device(client);
	}


	client = dvb->i2c_client_demod;
	if (client) {
		module_put(client->dev.driver->owner);
		i2c_unregister_device(client);
	}

	em28xx_unregister_dvb(dvb);
	kfree(dvb);
	dev->dvb = NULL;
	kref_put(&dev->ref, em28xx_free_device);

	return 0;
}
