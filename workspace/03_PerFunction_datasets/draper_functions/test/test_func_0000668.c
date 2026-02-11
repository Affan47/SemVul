__oxu_urb_enqueue(struct usb_hcd *hcd, struct urb *urb,
				gfp_t mem_flags)
{
	struct oxu_hcd *oxu = hcd_to_oxu(hcd);
	struct list_head qtd_list;

	INIT_LIST_HEAD(&qtd_list);

	switch (usb_pipetype(urb->pipe)) {
	case PIPE_CONTROL:
	case PIPE_BULK:
	default:
		if (!qh_urb_transaction(oxu, urb, &qtd_list, mem_flags))
			return -ENOMEM;
		return submit_async(oxu, urb, &qtd_list, mem_flags);

	case PIPE_INTERRUPT:
		if (!qh_urb_transaction(oxu, urb, &qtd_list, mem_flags))
			return -ENOMEM;
		return intr_submit(oxu, urb, &qtd_list, mem_flags);

	case PIPE_ISOCHRONOUS:
		if (urb->dev->speed == USB_SPEED_HIGH)
			return itd_submit(oxu, urb, mem_flags);
		else
			return sitd_submit(oxu, urb, mem_flags);
	}
}
