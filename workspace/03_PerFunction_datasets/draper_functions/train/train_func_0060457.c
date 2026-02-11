b43_radio_2059_init(struct b43_wldev *dev)
{
	const u16 routing[] = { R2059_C1, R2059_C2, R2059_C3 };
	int i;


	b43_radio_2059_init_pre(dev);

	r2059_upload_inittabs(dev);

	for (i = 0; i < ARRAY_SIZE(routing); i++)
		b43_radio_set(dev, routing[i] | 0x146, 0x3);


	b43_radio_set(dev, R2059_RFPLL_MISC_CAL_RESETN, 0x0078);
	b43_radio_set(dev, R2059_XTAL_CONFIG2, 0x0080);
	msleep(2);
	b43_radio_mask(dev, R2059_RFPLL_MISC_CAL_RESETN, ~0x0078);
	b43_radio_mask(dev, R2059_XTAL_CONFIG2, ~0x0080);

	if (1) {
		b43_radio_2059_rcal(dev);
		b43_radio_2057_rccal(dev);
	}

	b43_radio_mask(dev, R2059_RFPLL_MASTER, ~0x0008);
}
