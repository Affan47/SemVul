xhci_add_ep_to_interval_table(struct xhci_hcd *xhci,
		struct xhci_bw_info *ep_bw,
		struct xhci_interval_bw_table *bw_table,
		struct usb_device *udev,
		struct xhci_virt_ep *virt_ep,
		struct xhci_tt_bw_info *tt_info)
{
	struct xhci_interval_bw	*interval_bw;
	struct xhci_virt_ep *smaller_ep;
	int normalized_interval;

	if (xhci_is_async_ep(ep_bw->type))
		return;

	if (udev->speed == USB_SPEED_SUPER) {
		if (xhci_is_sync_in_ep(ep_bw->type))
			xhci->devs[udev->slot_id]->bw_table->ss_bw_in +=
				xhci_get_ss_bw_consumed(ep_bw);
		else
			xhci->devs[udev->slot_id]->bw_table->ss_bw_out +=
				xhci_get_ss_bw_consumed(ep_bw);
		return;
	}


	if (udev->speed == USB_SPEED_HIGH)
		normalized_interval = ep_bw->ep_interval;
	else
		normalized_interval = ep_bw->ep_interval - 3;

	if (normalized_interval == 0)
		bw_table->interval0_esit_payload += ep_bw->max_esit_payload;
	interval_bw = &bw_table->interval_bw[normalized_interval];
	interval_bw->num_packets += ep_bw->num_packets;
	switch (udev->speed) {
	case USB_SPEED_LOW:
		interval_bw->overhead[LS_OVERHEAD_TYPE] += 1;
		break;
	case USB_SPEED_FULL:
		interval_bw->overhead[FS_OVERHEAD_TYPE] += 1;
		break;
	case USB_SPEED_HIGH:
		interval_bw->overhead[HS_OVERHEAD_TYPE] += 1;
		break;
	case USB_SPEED_SUPER:
	case USB_SPEED_SUPER_PLUS:
	case USB_SPEED_UNKNOWN:
	case USB_SPEED_WIRELESS:


		return;
	}

	if (tt_info)
		tt_info->active_eps += 1;

	list_for_each_entry(smaller_ep, &interval_bw->endpoints,
			bw_endpoint_list) {
		if (ep_bw->max_packet_size >=
				smaller_ep->bw_info.max_packet_size) {

			list_add_tail(&virt_ep->bw_endpoint_list,
					&smaller_ep->bw_endpoint_list);
			return;
		}
	}

	list_add_tail(&virt_ep->bw_endpoint_list,
			&interval_bw->endpoints);
}
