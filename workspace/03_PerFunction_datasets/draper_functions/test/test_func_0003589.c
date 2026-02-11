xmit_wait_timer_func(unsigned long opaque)
{
	struct qib_pportdata *ppd = (struct qib_pportdata *)opaque;
	struct qib_devdata *dd = dd_from_ppd(ppd);
	unsigned long flags;
	u8 status;

	spin_lock_irqsave(&ppd->ibport_data.lock, flags);
	if (ppd->cong_stats.flags == IB_PMA_CONG_HW_CONTROL_SAMPLE) {
		status = dd->f_portcntr(ppd, QIBPORTCNTR_PSSTAT);
		if (status == IB_PMA_SAMPLE_STATUS_DONE) {

			cache_hw_sample_counters(ppd);
			ppd->cong_stats.flags = IB_PMA_CONG_HW_CONTROL_TIMER;
		} else
			goto done;
	}
	ppd->cong_stats.counter = xmit_wait_get_value_delta(ppd);
	dd->f_set_cntr_sample(ppd, QIB_CONG_TIMER_PSINTERVAL, 0x0);
done:
	spin_unlock_irqrestore(&ppd->ibport_data.lock, flags);
	mod_timer(&ppd->cong_stats.timer, jiffies + HZ);
}
