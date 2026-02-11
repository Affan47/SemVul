b43_nphy_reapply_tx_cal_coeffs(struct b43_wldev *dev)
{
	struct b43_phy_n *nphy = dev->phy.n;
	u8 i;
	u16 buffer[7];
	bool equal = true;

	if (!nphy->txiqlocal_coeffsvalid ||
	    nphy->txiqlocal_chanspec.center_freq != dev->phy.chandef->chan->center_freq ||
	    nphy->txiqlocal_chanspec.channel_type != cfg80211_get_chandef_type(dev->phy.chandef))
		return;

	b43_ntab_read_bulk(dev, B43_NTAB16(15, 80), 7, buffer);
	for (i = 0; i < 4; i++) {
		if (buffer[i] != nphy->txiqlocal_bestc[i]) {
			equal = false;
			break;
		}
	}

	if (!equal) {
		b43_ntab_write_bulk(dev, B43_NTAB16(15, 80), 4,
					nphy->txiqlocal_bestc);
		for (i = 0; i < 4; i++)
			buffer[i] = 0;
		b43_ntab_write_bulk(dev, B43_NTAB16(15, 88), 4,
					buffer);
		b43_ntab_write_bulk(dev, B43_NTAB16(15, 85), 2,
					&nphy->txiqlocal_bestc[5]);
		b43_ntab_write_bulk(dev, B43_NTAB16(15, 93), 2,
					&nphy->txiqlocal_bestc[5]);
	}
}
