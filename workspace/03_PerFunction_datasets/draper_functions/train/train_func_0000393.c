b43_nphy_get_tx_gain_table(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	enum ieee80211_band band = b43_current_band(dev->wl);
	struct ssb_sprom *sprom = dev->dev->bus_sprom;

	if (dev->phy.rev < 3)
		return b43_ntab_tx_gain_rev0_1_2;


	if ((dev->phy.n->ipa2g_on && band == IEEE80211_BAND_2GHZ) ||
	    (dev->phy.n->ipa5g_on && band == IEEE80211_BAND_5GHZ)) {
		return b43_nphy_get_ipa_gain_table(dev);
	} else if (b43_current_band(dev->wl) == IEEE80211_BAND_5GHZ) {
		switch (phy->rev) {
		case 6:
		case 5:
			return b43_ntab_tx_gain_epa_rev5_5g;
		case 4:
			return sprom->fem.ghz5.extpa_gain == 3 ?
				b43_ntab_tx_gain_epa_rev4_5g :
				b43_ntab_tx_gain_epa_rev4_hi_pwr_5g;
		case 3:
			return b43_ntab_tx_gain_epa_rev3_5g;
		default:
			b43err(dev->wl,
			       "No 5GHz EPA gain table available for this device\n");
			return NULL;
		}
	} else {
		switch (phy->rev) {
		case 6:
		case 5:
			if (sprom->fem.ghz2.extpa_gain == 3)
				return b43_ntab_tx_gain_epa_rev3_hi_pwr_2g;

		case 4:
		case 3:
			return b43_ntab_tx_gain_epa_rev3_2g;
		default:
			b43err(dev->wl,
			       "No 2GHz EPA gain table available for this device\n");
			return NULL;
		}
	}
}
