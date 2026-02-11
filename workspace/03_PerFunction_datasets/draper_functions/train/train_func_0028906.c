rt2500pci_config_channel(struct rt2x00_dev *rt2x00dev,
				     struct rf_channel *rf, const int txpower)
{
	u8 r70;


	rt2x00_set_field32(&rf->rf3, RF3_TXPOWER, TXPOWER_TO_DEV(txpower));


	if (!rt2x00_rf(rt2x00dev, RF2523))
		rt2x00_set_field32(&rf->rf1, RF1_TUNER, 1);
	rt2x00_set_field32(&rf->rf3, RF3_TUNER, 1);


	if (rt2x00_rf(rt2x00dev, RF2525)) {
		static const u32 vals[] = {
			0x00080cbe, 0x00080d02, 0x00080d06, 0x00080d0a,
			0x00080d0e, 0x00080d12, 0x00080d16, 0x00080d1a,
			0x00080d1e, 0x00080d22, 0x00080d26, 0x00080d2a,
			0x00080d2e, 0x00080d3a
		};

		rt2500pci_rf_write(rt2x00dev, 1, rf->rf1);
		rt2500pci_rf_write(rt2x00dev, 2, vals[rf->channel - 1]);
		rt2500pci_rf_write(rt2x00dev, 3, rf->rf3);
		if (rf->rf4)
			rt2500pci_rf_write(rt2x00dev, 4, rf->rf4);
	}

	rt2500pci_rf_write(rt2x00dev, 1, rf->rf1);
	rt2500pci_rf_write(rt2x00dev, 2, rf->rf2);
	rt2500pci_rf_write(rt2x00dev, 3, rf->rf3);
	if (rf->rf4)
		rt2500pci_rf_write(rt2x00dev, 4, rf->rf4);


	r70 = 0x46;
	rt2x00_set_field8(&r70, BBP_R70_JAPAN_FILTER, rf->channel == 14);
	rt2500pci_bbp_write(rt2x00dev, 70, r70);

	msleep(1);


	if (!rt2x00_rf(rt2x00dev, RF2523)) {
		rt2x00_set_field32(&rf->rf1, RF1_TUNER, 0);
		rt2500pci_rf_write(rt2x00dev, 1, rf->rf1);
	}

	rt2x00_set_field32(&rf->rf3, RF3_TUNER, 0);
	rt2500pci_rf_write(rt2x00dev, 3, rf->rf3);


	rt2x00mmio_register_read(rt2x00dev, CNT0, &rf->rf1);
}
