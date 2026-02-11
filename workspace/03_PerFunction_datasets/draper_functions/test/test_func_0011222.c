au0828_card_setup(struct au0828_dev *dev)
{
	static u8 eeprom[256];

	dprintk(1, "%s()\n", __func__);

	if (dev->i2c_rc == 0) {
		dev->i2c_client.addr = 0xa0 >> 1;
		tveeprom_read(&dev->i2c_client, eeprom, sizeof(eeprom));
	}

	switch (dev->boardnr) {
	case AU0828_BOARD_HAUPPAUGE_HVR850:
	case AU0828_BOARD_HAUPPAUGE_HVR950Q:
	case AU0828_BOARD_HAUPPAUGE_HVR950Q_MXL:
	case AU0828_BOARD_HAUPPAUGE_WOODBURY:
		if (dev->i2c_rc == 0)
			hauppauge_eeprom(dev, eeprom+0xa0);
		break;
	}

	au0828_card_analog_fe_setup(dev);
}
