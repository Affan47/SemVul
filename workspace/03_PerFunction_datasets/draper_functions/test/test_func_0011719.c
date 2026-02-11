wpa_mlme(struct net_device *dev, u32 command, u32 reason)
{
	struct _adapter *padapter = netdev_priv(dev);

	switch (command) {
	case IEEE_MLME_STA_DEAUTH:
		if (!r8712_set_802_11_disassociate(padapter))
			return -1;
		break;
	case IEEE_MLME_STA_DISASSOC:
		if (!r8712_set_802_11_disassociate(padapter))
			return -1;
		break;
	default:
		return -EOPNOTSUPP;
	}
	return 0;
}
