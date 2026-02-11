rtw_pm_set_ips(struct adapter *padapter, u8 mode)
{
	struct pwrctrl_priv *pwrctrlpriv = &padapter->pwrctrlpriv;

	if (mode == IPS_NORMAL || mode == IPS_LEVEL_2) {
		rtw_ips_mode_req(pwrctrlpriv, mode);
		DBG_88E("%s %s\n", __func__, mode == IPS_NORMAL ? "IPS_NORMAL" : "IPS_LEVEL_2");
		return 0;
	} else if (mode == IPS_NONE) {
		rtw_ips_mode_req(pwrctrlpriv, mode);
		DBG_88E("%s %s\n", __func__, "IPS_NONE");
		if ((padapter->bSurpriseRemoved == 0) && (_FAIL == rtw_pwr_wakeup(padapter)))
			return -EFAULT;
	} else {
		return -EINVAL;
	}
	return 0;
}
