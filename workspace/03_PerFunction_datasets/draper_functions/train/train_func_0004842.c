rtw_ps_processor23a(struct rtw_adapter *padapter)
{
	struct pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;

	pwrpriv->ps_processing = true;

	if (pwrpriv->bips_processing == true)
		goto exit;

	if (pwrpriv->ips_mode_req == IPS_NONE)
		goto exit;

	if (!rtw_pwr_unassociated_idle(padapter))
		goto exit;

	if (pwrpriv->rf_pwrstate == rf_on &&
	    (pwrpriv->pwr_state_check_cnts % 4) == 0) {
		DBG_8723A("==>%s .fw_state(%x)\n", __func__,
			  get_fwstate(pmlmepriv));
		pwrpriv->change_rfpwrstate = rf_off;
		ips_enter23a(padapter);
	}
exit:
	rtw_set_pwr_state_check_timer(&padapter->pwrctrlpriv);
	pwrpriv->ps_processing = false;
}
