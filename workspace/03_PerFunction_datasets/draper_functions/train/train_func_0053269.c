enic_busy_poll(struct napi_struct *napi)
{
	struct net_device *netdev = napi->dev;
	struct enic *enic = netdev_priv(netdev);
	unsigned int rq = (napi - &enic->napi[0]);
	unsigned int cq = enic_cq_rq(enic, rq);
	unsigned int intr = enic_msix_rq_intr(enic, rq);
	unsigned int work_to_do = -1;
	unsigned int work_done;

	if (!enic_poll_lock_poll(&enic->rq[rq]))
		return LL_FLUSH_BUSY;
	work_done = vnic_cq_service(&enic->cq[cq], work_to_do,
				    enic_rq_service, NULL);

	if (work_done > 0)
		vnic_intr_return_credits(&enic->intr[intr],
					 work_done, 0, 0);
	vnic_rq_fill(&enic->rq[rq], enic_rq_alloc_buf);
	if (enic->rx_coalesce_setting.use_adaptive_rx_coalesce)
		enic_calc_int_moderation(enic, &enic->rq[rq]);
	enic_poll_unlock_poll(&enic->rq[rq]);

	return work_done;
}
