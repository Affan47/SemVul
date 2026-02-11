xhci_stop_watchdog_timer_in_irq(struct xhci_hcd *xhci,
		struct xhci_virt_ep *ep)
{
	ep->ep_state &= ~EP_HALT_PENDING;


	if (del_timer(&ep->stop_cmd_timer))
		ep->stop_cmds_pending--;
}
