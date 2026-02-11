hauppauge_eeprom(struct cx23885_dev *dev, u8 *eeprom_data)
{
	struct tveeprom tv;

	tveeprom_hauppauge_analog(&dev->i2c_bus[0].i2c_client, &tv,
		eeprom_data);


	switch (tv.model) {
	case 22001:


	case 22009:


	case 22011:


	case 22019:


	case 22021:


	case 22029:


	case 22101:


	case 22109:


	case 22111:


	case 22119:


	case 22121:


	case 22129:


	case 71009:


	case 71100:


	case 71359:


	case 71439:


	case 71449:


	case 71939:


	case 71949:


	case 71959:


	case 71979:


	case 71999:


	case 76601:


	case 77001:


	case 77011:


	case 77041:


	case 77051:


	case 78011:


	case 78501:


	case 78521:


	case 78531:


	case 78631:


	case 79001:


	case 79101:


	case 79501:


	case 79561:


	case 79571:


	case 79671:


	case 80019:


	case 81509:


	case 81519:


		break;
	case 85021:


		break;
	case 85721:


	case 150329:

		break;
	default:
		printk(KERN_WARNING "%s: warning: "
			"unknown hauppauge model #%d\n",
			dev->name, tv.model);
		break;
	}

	printk(KERN_INFO "%s: hauppauge eeprom: model=%d\n",
			dev->name, tv.model);
}
