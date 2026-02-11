rtw_hal_mgnt_xmit(struct adapter *adapt, struct xmit_frame *pmgntframe)
{
	s32 ret = _FAIL;

	if (adapt->HalFunc.mgnt_xmit)
		ret = adapt->HalFunc.mgnt_xmit(adapt, pmgntframe);
	return ret;
}
