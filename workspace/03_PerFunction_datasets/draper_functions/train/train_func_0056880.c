init_dummy_udc_hw(struct dummy *dum)
{
	int i;

	INIT_LIST_HEAD(&dum->gadget.ep_list);
	for (i = 0; i < DUMMY_ENDPOINTS; i++) {
		struct dummy_ep	*ep = &dum->ep[i];

		if (!ep_info[i].name)
			break;
		ep->ep.name = ep_info[i].name;
		ep->ep.caps = ep_info[i].caps;
		ep->ep.ops = &dummy_ep_ops;
		list_add_tail(&ep->ep.ep_list, &dum->gadget.ep_list);
		ep->halted = ep->wedged = ep->already_seen =
				ep->setup_stage = 0;
		usb_ep_set_maxpacket_limit(&ep->ep, ~0);
		ep->ep.max_streams = 16;
		ep->last_io = jiffies;
		ep->gadget = &dum->gadget;
		ep->desc = NULL;
		INIT_LIST_HEAD(&ep->queue);
	}

	dum->gadget.ep0 = &dum->ep[0].ep;
	list_del_init(&dum->ep[0].ep.ep_list);
	INIT_LIST_HEAD(&dum->fifo_req.queue);

#ifdef CONFIG_USB_OTG
	dum->gadget.is_otg = 1;
#endif
}
