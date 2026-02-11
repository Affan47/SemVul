xgbe_get_hwtstamp_settings(struct xgbe_prv_data *pdata,
				      struct ifreq *ifreq)
{
	if (copy_to_user(ifreq->ifr_data, &pdata->tstamp_config,
			 sizeof(pdata->tstamp_config)))
		return -EFAULT;

	return 0;
}
