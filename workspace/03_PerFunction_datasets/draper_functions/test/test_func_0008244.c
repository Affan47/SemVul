musb_deassert_reset(struct work_struct *work)
{
	struct musb *musb;
	unsigned long flags;

	musb = container_of(work, struct musb, deassert_reset_work.work);

	spin_lock_irqsave(&musb->lock, flags);

	if (musb->port1_status & USB_PORT_STAT_RESET)
		musb_port_reset(musb, false);

	spin_unlock_irqrestore(&musb->lock, flags);
}
