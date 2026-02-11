snd_ice1712_chip_init(struct snd_ice1712 *ice)
{
	outb(ICE1712_RESET | ICE1712_NATIVE, ICEREG(ice, CONTROL));
	udelay(200);
	outb(ICE1712_NATIVE, ICEREG(ice, CONTROL));
	udelay(200);
	if (ice->eeprom.subvendor == ICE1712_SUBDEVICE_DMX6FIRE &&
	    !ice->dxr_enable)


		ice->eeprom.data[ICE_EEP1_CODEC] = 0x3a;
	pci_write_config_byte(ice->pci, 0x60, ice->eeprom.data[ICE_EEP1_CODEC]);
	pci_write_config_byte(ice->pci, 0x61, ice->eeprom.data[ICE_EEP1_ACLINK]);
	pci_write_config_byte(ice->pci, 0x62, ice->eeprom.data[ICE_EEP1_I2SID]);
	pci_write_config_byte(ice->pci, 0x63, ice->eeprom.data[ICE_EEP1_SPDIF]);
	if (ice->eeprom.subvendor != ICE1712_SUBDEVICE_STDSP24) {
		ice->gpio.write_mask = ice->eeprom.gpiomask;
		ice->gpio.direction = ice->eeprom.gpiodir;
		snd_ice1712_write(ice, ICE1712_IREG_GPIO_WRITE_MASK,
				  ice->eeprom.gpiomask);
		snd_ice1712_write(ice, ICE1712_IREG_GPIO_DIRECTION,
				  ice->eeprom.gpiodir);
		snd_ice1712_write(ice, ICE1712_IREG_GPIO_DATA,
				  ice->eeprom.gpiostate);
	} else {
		ice->gpio.write_mask = 0xc0;
		ice->gpio.direction = 0xff;
		snd_ice1712_write(ice, ICE1712_IREG_GPIO_WRITE_MASK, 0xc0);
		snd_ice1712_write(ice, ICE1712_IREG_GPIO_DIRECTION, 0xff);
		snd_ice1712_write(ice, ICE1712_IREG_GPIO_DATA,
				  ICE1712_STDSP24_CLOCK_BIT);
	}
	snd_ice1712_write(ice, ICE1712_IREG_PRO_POWERDOWN, 0);
	if (!(ice->eeprom.data[ICE_EEP1_CODEC] & ICE1712_CFG_NO_CON_AC97)) {
		outb(ICE1712_AC97_WARM, ICEREG(ice, AC97_CMD));
		udelay(100);
		outb(0, ICEREG(ice, AC97_CMD));
		udelay(200);
		snd_ice1712_write(ice, ICE1712_IREG_CONSUMER_POWERDOWN, 0);
	}
	snd_ice1712_set_pro_rate(ice, 48000, 1);

	outb(((ice->eeprom.data[ICE_EEP1_CODEC] & ICE1712_CFG_2xMPU401) == 0 ?
	      ICE1712_IRQ_MPU2 : 0) |
	     ((ice->eeprom.data[ICE_EEP1_CODEC] & ICE1712_CFG_NO_CON_AC97) ?
	      ICE1712_IRQ_PBKDS | ICE1712_IRQ_CONCAP | ICE1712_IRQ_CONPBK : 0),
	     ICEREG(ice, IRQMASK));
	outb(0x00, ICEMT(ice, IRQ));

	return 0;
}
