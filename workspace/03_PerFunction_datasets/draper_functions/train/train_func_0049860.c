rtw_if_up23a(struct rtw_adapter *padapter)
{
	int res;

	if (padapter->bDriverStopped || padapter->bSurpriseRemoved ||
	    !check_fwstate(&padapter->mlmepriv, _FW_LINKED)) {
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_,
			 "rtw_if_up23a:bDriverStopped(%d) OR bSurpriseRemoved(%d)\n",
			 padapter->bDriverStopped, padapter->bSurpriseRemoved);
		res = false;
	} else
		res =  true;

	return res;
}
