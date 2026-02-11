r871x_dev_unload(struct _adapter *padapter)
{
	if (padapter->bup) {

		padapter->bDriverStopped = true;


		rtl871x_intf_stop(padapter);


		r8712_stop_drv_threads(padapter);


		if (!padapter->bSurpriseRemoved) {
			padapter->hw_init_completed = false;
			rtl8712_hal_deinit(padapter);
		}


		if (padapter->dvobj_deinit)
			padapter->dvobj_deinit(padapter);
		padapter->bup = false;
	}
}
