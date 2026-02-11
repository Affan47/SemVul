i40e_ptp_create_clock(struct i40e_pf *pf)
{

	if (!IS_ERR_OR_NULL(pf->ptp_clock))
		return 0;

	strncpy(pf->ptp_caps.name, i40e_driver_name, sizeof(pf->ptp_caps.name));
	pf->ptp_caps.owner = THIS_MODULE;
	pf->ptp_caps.max_adj = 999999999;
	pf->ptp_caps.n_ext_ts = 0;
	pf->ptp_caps.pps = 0;
	pf->ptp_caps.adjfreq = i40e_ptp_adjfreq;
	pf->ptp_caps.adjtime = i40e_ptp_adjtime;
	pf->ptp_caps.gettime64 = i40e_ptp_gettime;
	pf->ptp_caps.settime64 = i40e_ptp_settime;
	pf->ptp_caps.enable = i40e_ptp_feature_enable;


	pf->ptp_clock = ptp_clock_register(&pf->ptp_caps, &pf->pdev->dev);
	if (IS_ERR(pf->ptp_clock))
		return PTR_ERR(pf->ptp_clock);


	pf->tstamp_config.rx_filter = HWTSTAMP_FILTER_NONE;
	pf->tstamp_config.tx_type = HWTSTAMP_TX_OFF;

	return 0;
}
