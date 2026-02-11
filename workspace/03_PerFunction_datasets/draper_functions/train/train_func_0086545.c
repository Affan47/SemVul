xgbe_set_mode(struct xgbe_prv_data *pdata,
			  enum xgbe_mode mode)
{
	enum xgbe_mode cur_mode;

	xgbe_cur_mode(pdata, &cur_mode);
	if (mode != cur_mode)
		xgbe_switch_mode(pdata);
}
