get_rx_struct(struct rx_cxt *rx)
{
	struct usb_rx *r;

	if (list_empty(&rx->free_list)) {
		r = alloc_rx_struct(rx);
		if (!r)
			return NULL;

		list_add(&r->list, &rx->free_list);
	}

	r = list_entry(rx->free_list.next, struct usb_rx, list);
	list_move_tail(&r->list, &rx->used_list);

	return r;
}
