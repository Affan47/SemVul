udc_enable_ep0_interrupts(struct udc *dev)
{
	u32 tmp;

	DBG(dev, "udc_enable_ep0_interrupts()\n");


	tmp = readl(&dev->regs->ep_irqmsk);

	tmp &= AMD_UNMASK_BIT(UDC_EPINT_IN_EP0)
		& AMD_UNMASK_BIT(UDC_EPINT_OUT_EP0);
	writel(tmp, &dev->regs->ep_irqmsk);

	return 0;
}
