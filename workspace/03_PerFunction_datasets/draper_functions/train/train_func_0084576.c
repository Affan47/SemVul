mv_udc_wakeup(struct usb_gadget *gadget)
{
	struct mv_udc *udc = container_of(gadget, struct mv_udc, gadget);
	u32 portsc;


	if (!udc->remote_wakeup)
		return -ENOTSUPP;

	portsc = readl(&udc->op_regs->portsc);

	if (!(portsc & PORTSCX_PORT_SUSPEND))
		return 0;

	portsc |= PORTSCX_PORT_FORCE_RESUME;
	writel(portsc, &udc->op_regs->portsc[0]);
	return 0;
}
