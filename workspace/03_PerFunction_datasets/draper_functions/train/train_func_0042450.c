b43_wa_rssi_adc(struct b43_wldev *dev)
{
	if (dev->phy.analog == 4)
		b43_phy_write(dev, 0x00DC, 0x7454);
}
