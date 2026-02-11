DCD_WriteEmptyTxFifo(USB_OTG_CORE_HANDLE *pdev, uint32_t epnum) {
	USB_OTG_DTXFSTSn_TypeDef  txstatus;
	USB_OTG_EP *ep;
	uint32_t len = 0;
	uint32_t len32b;
	txstatus.d32 = 0;

	ep = &pdev->dev.in_ep[epnum];

	len = ep->xfer_len - ep->xfer_count;

	if (len > ep->maxpacket) {
		len = ep->maxpacket;
	}

	len32b = (len + 3) / 4;
	txstatus.d32 = USB_OTG_READ_REG32( &pdev->regs.INEP_REGS[epnum]->DTXFSTS);


	while  (txstatus.b.txfspcavail > len32b &&
			ep->xfer_count < ep->xfer_len &&
			ep->xfer_len != 0) {

		len = ep->xfer_len - ep->xfer_count;

		if (len > ep->maxpacket) {
			len = ep->maxpacket;
		}
		len32b = (len + 3) / 4;

		USB_OTG_WritePacket (pdev , ep->xfer_buff, epnum, len);

		ep->xfer_buff  += len;
		ep->xfer_count += len;


		if (ep->xfer_count >= ep->xfer_len) {
			uint32_t fifoemptymsk = 1 << ep->num;
			USB_OTG_MODIFY_REG32(&pdev->regs.DREGS->DIEPEMPMSK, fifoemptymsk, 0);
			break;
		}

		txstatus.d32 = USB_OTG_READ_REG32(&pdev->regs.INEP_REGS[epnum]->DTXFSTS);
	}

	return 1;
}
