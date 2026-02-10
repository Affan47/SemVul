udc_free_request(struct usb_ep *usbep, struct usb_request *usbreq)
{
	struct udc_ep	*ep;
	struct udc_request	*req;

	if (!usbep || !usbreq)
		return;

	ep = container_of(usbep, struct udc_ep, ep);
	req = container_of(usbreq, struct udc_request, req);
	VDBG(ep->dev, "free_req req=%p\n", req);
	BUG_ON(!list_empty(&req->queue));
	if (req->td_data) {
		VDBG(ep->dev, "req->td_data=%p\n", req->td_data);


		if (req->chain_len > 1)
			udc_free_dma_chain(ep->dev, req);

		pci_pool_free(ep->dev->data_requests, req->td_data,
							req->td_phys);
	}
	kfree(req);
}
