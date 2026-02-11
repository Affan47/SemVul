zd_tx_watchdog_disable(struct zd_usb *usb)
{
	struct zd_usb_tx *tx = &usb->tx;

	if (tx->watchdog_enabled) {
		dev_dbg_f(zd_usb_dev(usb), "\n");
		tx->watchdog_enabled = 0;
		cancel_delayed_work_sync(&tx->watchdog_work);
	}
}
