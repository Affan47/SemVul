xgbe_write_rss_reg(struct xgbe_prv_data *pdata, unsigned int type,
			      unsigned int index, unsigned int val)
{
	unsigned int wait;
	int ret = 0;

	mutex_lock(&pdata->rss_mutex);

	if (XGMAC_IOREAD_BITS(pdata, MAC_RSSAR, OB)) {
		ret = -EBUSY;
		goto unlock;
	}

	XGMAC_IOWRITE(pdata, MAC_RSSDR, val);

	XGMAC_IOWRITE_BITS(pdata, MAC_RSSAR, RSSIA, index);
	XGMAC_IOWRITE_BITS(pdata, MAC_RSSAR, ADDRT, type);
	XGMAC_IOWRITE_BITS(pdata, MAC_RSSAR, CT, 0);
	XGMAC_IOWRITE_BITS(pdata, MAC_RSSAR, OB, 1);

	wait = 1000;
	while (wait--) {
		if (!XGMAC_IOREAD_BITS(pdata, MAC_RSSAR, OB))
			goto unlock;

		usleep_range(1000, 1500);
	}

	ret = -EBUSY;

unlock:
	mutex_unlock(&pdata->rss_mutex);

	return ret;
}
