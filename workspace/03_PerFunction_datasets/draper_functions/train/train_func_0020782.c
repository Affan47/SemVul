pch_udc_complete_transfer(struct pch_udc_ep *ep)
{
	struct pch_udc_request *req;
	struct pch_udc_dev *dev = ep->dev;

	if (list_empty(&ep->queue))
		return;
	req = list_entry(ep->queue.next, struct pch_udc_request, queue);
	if ((req->td_data_last->status & PCH_UDC_BUFF_STS) !=
	    PCH_UDC_BS_DMA_DONE)
		return;
	if ((req->td_data_last->status & PCH_UDC_RXTX_STS) !=
	     PCH_UDC_RTS_SUCC) {
		dev_err(&dev->pdev->dev, "Invalid RXTX status (0x%08x) "
			"epstatus=0x%08x\n",
		       (req->td_data_last->status & PCH_UDC_RXTX_STS),
		       (int)(ep->epsts));
		return;
	}

	req->req.actual = req->req.length;
	req->td_data_last->status = PCH_UDC_BS_HST_BSY | PCH_UDC_DMA_LAST;
	req->td_data->status = PCH_UDC_BS_HST_BSY | PCH_UDC_DMA_LAST;
	complete_req(ep, req, 0);
	req->dma_going = 0;
	if (!list_empty(&ep->queue)) {
		pch_udc_wait_ep_stall(ep);
		pch_udc_ep_clear_nak(ep);
		pch_udc_enable_ep_interrupts(ep->dev,
					     PCH_UDC_EPINT(ep->in, ep->num));
	} else {
		pch_udc_disable_ep_interrupts(ep->dev,
					      PCH_UDC_EPINT(ep->in, ep->num));
	}
}
