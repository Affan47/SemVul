dbgp_reset_prep(struct usb_hcd *hcd)
{
	int ret = xen_dbgp_reset_prep(hcd);
	u32 ctrl;

	if (ret)
		return ret;

	dbgp_not_safe = 1;
	if (!ehci_debug)
		return 0;

	if ((early_dbgp_console.index != -1 &&
	     !(early_dbgp_console.flags & CON_BOOT)) ||
	    dbgp_kgdb_mode)
		return 1;


	ctrl = readl(&ehci_debug->control);
	if (ctrl & DBGP_ENABLED) {
		ctrl &= ~(DBGP_CLAIM);
		writel(ctrl, &ehci_debug->control);
	}
	return 0;
}
