enic_intr_coal_set_rx(struct enic *enic, u32 timer)
{
	int i;
	int intr;

	for (i = 0; i < enic->rq_count; i++) {
		intr = enic_msix_rq_intr(enic, i);
		vnic_intr_coalescing_timer_set(&enic->intr[intr], timer);
	}
}
