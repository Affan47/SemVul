dcd_change(struct slgt_info *info, unsigned short status)
{
	if (status & BIT1) {
		info->signals |= SerialSignal_DCD;
		info->input_signal_events.dcd_up++;
	} else {
		info->signals &= ~SerialSignal_DCD;
		info->input_signal_events.dcd_down++;
	}
	DBGISR(("dcd_change %s signals=%04X\n", info->device_name, info->signals));
	if ((info->dcd_chkcount)++ == IO_PIN_SHUTDOWN_LIMIT) {
		slgt_irq_off(info, IRQ_DCD);
		return;
	}
	info->icount.dcd++;
#if SYNCLINK_GENERIC_HDLC
	if (info->netcount) {
		if (info->signals & SerialSignal_DCD)
			netif_carrier_on(info->netdev);
		else
			netif_carrier_off(info->netdev);
	}
#endif
	wake_up_interruptible(&info->status_event_wait_q);
	wake_up_interruptible(&info->event_wait_q);
	info->pending_bh |= BH_STATUS;

	if (info->port.flags & ASYNC_CHECK_CD) {
		if (info->signals & SerialSignal_DCD)
			wake_up_interruptible(&info->port.open_wait);
		else {
			if (info->port.tty)
				tty_hangup(info->port.tty);
		}
	}
}
