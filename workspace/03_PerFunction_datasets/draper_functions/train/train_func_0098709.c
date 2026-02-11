default_baseband_attenuation(struct b43_wldev *dev,
					 struct b43_bbatt *bb)
{
	struct b43_phy *phy = &dev->phy;

	if (phy->radio_ver == 0x2050 && phy->radio_rev < 6)
		bb->att = 0;
	else
		bb->att = 2;
}
