pma_get_portsamplesresult(struct ib_pma_mad *pmp,
				     struct ib_device *ibdev, u8 port)
{
	struct ib_pma_portsamplesresult *p =
		(struct ib_pma_portsamplesresult *)pmp->data;
	struct qib_ibdev *dev = to_idev(ibdev);
	struct qib_devdata *dd = dd_from_dev(dev);
	struct qib_ibport *ibp = to_iport(ibdev, port);
	struct qib_pportdata *ppd = ppd_from_ibp(ibp);
	unsigned long flags;
	u8 status;
	int i;

	memset(pmp->data, 0, sizeof(pmp->data));
	spin_lock_irqsave(&ibp->lock, flags);
	p->tag = cpu_to_be16(ibp->pma_tag);
	if (ppd->cong_stats.flags == IB_PMA_CONG_HW_CONTROL_TIMER)
		p->sample_status = IB_PMA_SAMPLE_STATUS_DONE;
	else {
		status = dd->f_portcntr(ppd, QIBPORTCNTR_PSSTAT);
		p->sample_status = cpu_to_be16(status);
		if (status == IB_PMA_SAMPLE_STATUS_DONE) {
			cache_hw_sample_counters(ppd);
			ppd->cong_stats.counter =
				xmit_wait_get_value_delta(ppd);
			dd->f_set_cntr_sample(ppd,
					      QIB_CONG_TIMER_PSINTERVAL, 0);
			ppd->cong_stats.flags = IB_PMA_CONG_HW_CONTROL_TIMER;
		}
	}
	for (i = 0; i < ARRAY_SIZE(ibp->pma_counter_select); i++)
		p->counter[i] = cpu_to_be32(
			get_cache_hw_sample_counters(
				ppd, ibp->pma_counter_select[i]));
	spin_unlock_irqrestore(&ibp->lock, flags);

	return reply((struct ib_smp *) pmp);
}
