net2280_free_request(struct usb_ep *_ep, struct usb_request *_req)
{
	struct net2280_ep	*ep;
	struct net2280_request	*req;

	ep = container_of(_ep, struct net2280_ep, ep);
	if (!_ep || !_req) {
		dev_err(&ep->dev->pdev->dev, "%s: Inavlid ep=%p or req=%p\n",
							__func__, _ep, _req);
		return;
	}

	req = container_of(_req, struct net2280_request, req);
	WARN_ON(!list_empty(&req->queue));
	if (req->td)
		pci_pool_free(ep->dev->requests, req->td, req->td_dma);
	kfree(req);
}
