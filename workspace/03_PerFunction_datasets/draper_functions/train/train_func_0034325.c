USBD_DataOutStage(USB_OTG_CORE_HANDLE *pdev , uint8_t epnum) {
	USB_OTG_EP *ep;

	if(epnum == 0) {
		ep = &pdev->dev.out_ep[0];
		if ( pdev->dev.device_state == USB_OTG_EP0_DATA_OUT) {
			if(ep->rem_data_len > ep->maxpacket) {
				ep->rem_data_len -=  ep->maxpacket;

				if(pdev->cfg.dma_enable == 1) {

					ep->xfer_buff += ep->maxpacket;
				}
				USBD_CtlContinueRx (pdev,
									ep->xfer_buff,
									MIN(ep->rem_data_len ,ep->maxpacket));
			} else {
				if((pdev->dev.class_cb->EP0_RxReady != NULL)&&
						(pdev->dev.device_status == USB_OTG_CONFIGURED)) {
					pdev->dev.class_cb->EP0_RxReady(pdev);
				}
				USBD_CtlSendStatus(pdev);
			}
		}
	} else if((pdev->dev.class_cb->DataOut != NULL)&&
			  (pdev->dev.device_status == USB_OTG_CONFIGURED)) {
		pdev->dev.class_cb->DataOut(pdev, epnum);
	}
	return USBD_OK;
}
