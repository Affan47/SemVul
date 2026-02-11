t4_get_vpd_params(struct adapter *adapter, struct vpd_params *p)
{
	u32 cclk_param, cclk_val;
	int ret;


	ret = t4_get_raw_vpd_params(adapter, p);
	if (ret)
		return ret;


	cclk_param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		      FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_CCLK));
	ret = t4_query_params(adapter, adapter->mbox, adapter->pf, 0,
			      1, &cclk_param, &cclk_val);

	if (ret)
		return ret;
	p->cclk = cclk_val;

	return 0;
}
