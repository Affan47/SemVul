cx18_read_eeprom(struct cx18 *cx, struct tveeprom *tv)
{
	struct i2c_client *c;
	u8 eedata[256];

	memset(tv, 0, sizeof(*tv));

	c = kzalloc(sizeof(*c), GFP_KERNEL);
	if (!c)
		return;

	strlcpy(c->name, "cx18 tveeprom tmp", sizeof(c->name));
	c->adapter = &cx->i2c_adap[0];
	c->addr = 0xa0 >> 1;

	if (tveeprom_read(c, eedata, sizeof(eedata)))
		goto ret;

	switch (cx->card->type) {
	case CX18_CARD_HVR_1600_ESMT:
	case CX18_CARD_HVR_1600_SAMSUNG:
	case CX18_CARD_HVR_1600_S5H1411:
		tveeprom_hauppauge_analog(c, tv, eedata);
		break;
	case CX18_CARD_YUAN_MPC718:
	case CX18_CARD_GOTVIEW_PCI_DVD3:
		tv->model = 0x718;
		cx18_eeprom_dump(cx, eedata, sizeof(eedata));
		CX18_INFO("eeprom PCI ID: %02x%02x:%02x%02x\n",
			  eedata[2], eedata[1], eedata[4], eedata[3]);
		break;
	default:
		tv->model = 0xffffffff;
		cx18_eeprom_dump(cx, eedata, sizeof(eedata));
		break;
	}

ret:
	kfree(c);
}
