usb_gadget_unmap_request(struct usb_gadget *gadget,
		struct usb_request *req, int is_in)
{
	if (req->length == 0)
		return;

	if (req->num_mapped_sgs) {
		dma_unmap_sg(gadget->dev.parent, req->sg, req->num_mapped_sgs,
				is_in ? DMA_TO_DEVICE : DMA_FROM_DEVICE);

		req->num_mapped_sgs = 0;
	} else {
		dma_unmap_single(gadget->dev.parent, req->dma, req->length,
				is_in ? DMA_TO_DEVICE : DMA_FROM_DEVICE);
	}
}
