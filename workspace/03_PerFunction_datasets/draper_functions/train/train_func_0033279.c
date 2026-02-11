rtw_dev_unload(struct rtw_adapter *padapter)
{
	struct submit_ctx *pack_tx_ops = &padapter->xmitpriv.ack_tx_ops;

	RT_TRACE(_module_hci_intfs_c_, _drv_err_, "+rtw_dev_unload\n");

	if (padapter->bup) {
		DBG_8723A("===> rtw_dev_unload\n");

		padapter->bDriverStopped = true;
		if (padapter->xmitpriv.ack_tx)
			rtw23a_sctx_done_err(&pack_tx_ops,
					     RTW_SCTX_DONE_DRV_STOP);


		rtl8723a_usb_intf_stop(padapter);


		flush_workqueue(padapter->cmdpriv.wq);


		if (!padapter->bSurpriseRemoved) {
			rtl8723au_hal_deinit(padapter);
			padapter->bSurpriseRemoved = true;
		}
		padapter->bup = false;
	} else {
		RT_TRACE(_module_hci_intfs_c_, _drv_err_,
			 "r871x_dev_unload():padapter->bup == false\n");
	}
	DBG_8723A("<=== rtw_dev_unload\n");
	RT_TRACE(_module_hci_intfs_c_, _drv_err_, "-rtw_dev_unload\n");
}
