DCD_HandleInEP_ISR(USB_OTG_CORE_HANDLE *pdev) {
	USB_OTG_DIEPINTn_TypeDef  diepint;

	uint32_t ep_intr;
	uint32_t epnum = 0;
	uint32_t fifoemptymsk;
	diepint.d32 = 0;
	ep_intr = USB_OTG_ReadDevAllInEPItr(pdev);

	while ( ep_intr ) {
		if (ep_intr&0x1) {
			diepint.d32 = DCD_ReadDevInEP(pdev , epnum);
			if ( diepint.b.xfercompl ) {
				fifoemptymsk = 0x1 << epnum;
				USB_OTG_MODIFY_REG32(&pdev->regs.DREGS->DIEPEMPMSK, fifoemptymsk, 0);
				CLEAR_IN_EP_INTR(epnum, xfercompl);

				USBD_DCD_INT_fops->DataInStage(pdev , epnum);

				if (pdev->cfg.dma_enable == 1) {
					if((epnum == 0) && (pdev->dev.device_state == USB_OTG_EP0_STATUS_IN)) {

						USB_OTG_EP0_OutStart(pdev);
					}
				}
			}
			if ( diepint.b.timeout ) {
				CLEAR_IN_EP_INTR(epnum, timeout);
			}
			if (diepint.b.intktxfemp) {
				CLEAR_IN_EP_INTR(epnum, intktxfemp);
			}
			if (diepint.b.inepnakeff) {
				CLEAR_IN_EP_INTR(epnum, inepnakeff);
			}
			if ( diepint.b.epdisabled ) {
				CLEAR_IN_EP_INTR(epnum, epdisabled);
			}
			if (diepint.b.emptyintr) {

				DCD_WriteEmptyTxFifo(pdev , epnum);

				CLEAR_IN_EP_INTR(epnum, emptyintr);
			}
		}
		epnum++;
		ep_intr >>= 1;
	}

	return 1;
}
