r8711_wx_get_mode(struct net_device *dev, struct iw_request_info *a,
			     union iwreq_data *wrqu, char *b)
{
	struct _adapter *padapter = netdev_priv(dev);
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;

	if (check_fwstate(pmlmepriv, WIFI_STATION_STATE))
		wrqu->mode = IW_MODE_INFRA;
	else if (check_fwstate(pmlmepriv,
		 WIFI_ADHOC_MASTER_STATE | WIFI_ADHOC_STATE))
		wrqu->mode = IW_MODE_ADHOC;
	else if (check_fwstate(pmlmepriv, WIFI_AP_STATE))
		wrqu->mode = IW_MODE_MASTER;
	else
		wrqu->mode = IW_MODE_AUTO;
	return 0;
}
