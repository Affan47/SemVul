xudc_irq(int irq, void *_udc)
{
	struct xusb_udc *udc = _udc;
	u32 intrstatus;
	u32 ier;
	u8 index;
	u32 bufintr;
	unsigned long flags;

	spin_lock_irqsave(&udc->lock, flags);


	ier = udc->read_fn(udc->addr + XUSB_IER_OFFSET);
	ier &= ~XUSB_STATUS_INTR_EVENT_MASK;
	udc->write_fn(udc->addr, XUSB_IER_OFFSET, ier);


	intrstatus = udc->read_fn(udc->addr + XUSB_STATUS_OFFSET);


	if (intrstatus & XUSB_STATUS_INTR_EVENT_MASK) {


		xudc_startup_handler(udc, intrstatus);
	}


	if (intrstatus & XUSB_STATUS_INTR_BUFF_COMP_ALL_MASK) {

		ier = udc->read_fn(udc->addr + XUSB_IER_OFFSET);
		ier |= XUSB_STATUS_INTR_EVENT_MASK;
		udc->write_fn(udc->addr, XUSB_IER_OFFSET, ier);

		if (intrstatus & XUSB_STATUS_EP0_BUFF1_COMP_MASK)
			xudc_ctrl_ep_handler(udc, intrstatus);

		for (index = 1; index < 8; index++) {
			bufintr = ((intrstatus &
				  (XUSB_STATUS_EP1_BUFF1_COMP_MASK <<
				  (index - 1))) || (intrstatus &
				  (XUSB_STATUS_EP1_BUFF2_COMP_MASK <<
				  (index - 1))));
			if (bufintr) {
				xudc_nonctrl_ep_handler(udc, index,
							intrstatus);
			}
		}
	}

	spin_unlock_irqrestore(&udc->lock, flags);
	return IRQ_HANDLED;
}
