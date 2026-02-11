cfg_queues(struct adapter *adapter)
{
	struct sge *s = &adapter->sge;
	int q10g, n10g, qidx, pidx, qs;
	size_t iqe_size;


	BUG_ON((adapter->flags & (USING_MSIX|USING_MSI)) == 0);


	n10g = 0;
	for_each_port(adapter, pidx)
		n10g += is_x_10g_port(&adap2pinfo(adapter, pidx)->link_cfg);


	if (n10g == 0)
		q10g = 0;
	else {
		int n1g = (adapter->params.nports - n10g);
		q10g = (adapter->sge.max_ethqsets - n1g) / n10g;
		if (q10g > num_online_cpus())
			q10g = num_online_cpus();
	}


	qidx = 0;
	for_each_port(adapter, pidx) {
		struct port_info *pi = adap2pinfo(adapter, pidx);

		pi->first_qset = qidx;
		pi->nqsets = is_x_10g_port(&pi->link_cfg) ? q10g : 1;
		qidx += pi->nqsets;
	}
	s->ethqsets = qidx;


	iqe_size = 64;


	for (qs = 0; qs < s->max_ethqsets; qs++) {
		struct sge_eth_rxq *rxq = &s->ethrxq[qs];
		struct sge_eth_txq *txq = &s->ethtxq[qs];

		init_rspq(&rxq->rspq, 0, 0, 1024, iqe_size);
		rxq->fl.size = 72;
		txq->q.size = 1024;
	}


	init_rspq(&s->fw_evtq, SGE_TIMER_RSTRT_CNTR, 0, 512, iqe_size);


	init_rspq(&s->intrq, SGE_TIMER_RSTRT_CNTR, 0, MSIX_ENTRIES + 1,
		  iqe_size);
}
