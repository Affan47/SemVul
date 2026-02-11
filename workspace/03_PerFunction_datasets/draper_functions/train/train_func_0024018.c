netdev_open(struct net_device *pnetdev)
{
	struct _adapter *padapter = netdev_priv(pnetdev);

	mutex_lock(&padapter->mutex_start);
	if (!padapter->bup) {
		padapter->bDriverStopped = false;
		padapter->bSurpriseRemoved = false;
		padapter->bup = true;
		if (rtl871x_hal_init(padapter) != _SUCCESS)
			goto netdev_open_error;
		if (r8712_initmac == NULL)

			memcpy(pnetdev->dev_addr,
				padapter->eeprompriv.mac_addr, ETH_ALEN);
		else {


			msleep(200);
			r8712_setMacAddr_cmd(padapter, (u8 *)pnetdev->dev_addr);


			memcpy(padapter->eeprompriv.mac_addr,
				pnetdev->dev_addr, ETH_ALEN);
		}
		if (start_drv_threads(padapter) != _SUCCESS)
			goto netdev_open_error;
		if (padapter->dvobjpriv.inirp_init == NULL)
			goto netdev_open_error;
		else
			padapter->dvobjpriv.inirp_init(padapter);
		r8712_set_ps_mode(padapter, padapter->registrypriv.power_mgnt,
				  padapter->registrypriv.smart_ps);
	}
	if (!netif_queue_stopped(pnetdev))
		netif_start_queue(pnetdev);
	else
		netif_wake_queue(pnetdev);

	 if (video_mode)
		enable_video_mode(padapter, cbw40_enable);

	start_drv_timers(padapter);
	padapter->ledpriv.LedControlHandler(padapter, LED_CTL_NO_LINK);
	mutex_unlock(&padapter->mutex_start);
	return 0;
netdev_open_error:
	padapter->bup = false;
	netif_carrier_off(pnetdev);
	netif_stop_queue(pnetdev);
	mutex_unlock(&padapter->mutex_start);
	return -1;
}
