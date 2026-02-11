MSC_BOT_DataIn (USB_OTG_CORE_HANDLE  *pdev,
					 uint8_t epnum) {

#ifdef SDIO_DMA
	switch (MSC_BOT_State) {
		case BOT_DATA_IN:
			if(SCSI_ProcessCmd(pdev,
							   MSC_BOT_cbw.bLUN,
							   &MSC_BOT_cbw.CB[0]) < 0) {
				MSC_BOT_SendCSW (pdev, CSW_CMD_FAILED);
			}
			break;

		case BOT_SEND_DATA:
		case BOT_LAST_DATA_IN:
			MSC_BOT_SendCSW (pdev, CSW_CMD_PASSED);

			break;

		default:
			break;
	}
#endif
}
