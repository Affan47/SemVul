cx231xx_tuner_callback(void *ptr, int component, int command, int arg)
{
	int rc = 0;
	struct cx231xx *dev = ptr;

	if (dev->tuner_type == TUNER_XC5000) {
		if (command == XC5000_TUNER_RESET) {
			dev_dbg(dev->dev,
				"Tuner CB: RESET: cmd %d : tuner type %d\n",
				command, dev->tuner_type);
			cx231xx_set_gpio_value(dev, dev->board.tuner_gpio->bit,
					       1);
			msleep(10);
			cx231xx_set_gpio_value(dev, dev->board.tuner_gpio->bit,
					       0);
			msleep(330);
			cx231xx_set_gpio_value(dev, dev->board.tuner_gpio->bit,
					       1);
			msleep(10);
		}
	} else if (dev->tuner_type == TUNER_NXP_TDA18271) {
		switch (command) {
		case TDA18271_CALLBACK_CMD_AGC_ENABLE:
			if (dev->model == CX231XX_BOARD_PV_PLAYTV_USB_HYBRID)
				rc = cx231xx_set_agc_analog_digital_mux_select(dev, arg);
			break;
		default:
			rc = -EINVAL;
			break;
		}
	}
	return rc;
}
