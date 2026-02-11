t4_free_sge_resources(struct adapter *adap)
{
	int i;
	struct sge_eth_rxq *eq = adap->sge.ethrxq;
	struct sge_eth_txq *etq = adap->sge.ethtxq;


	for (i = 0; i < adap->sge.ethqsets; i++, eq++, etq++) {
		if (eq->rspq.desc)
			free_rspq_fl(adap, &eq->rspq,
				     eq->fl.size ? &eq->fl : NULL);
		if (etq->q.desc) {
			t4_eth_eq_free(adap, adap->mbox, adap->pf, 0,
				       etq->q.cntxt_id);
			free_tx_desc(adap, &etq->q, etq->q.in_use, true);
			kfree(etq->q.sdesc);
			free_txq(adap, &etq->q);
		}
	}


	t4_free_ofld_rxqs(adap, adap->sge.ofldqsets, adap->sge.ofldrxq);
	t4_free_ofld_rxqs(adap, adap->sge.rdmaqs, adap->sge.rdmarxq);
	t4_free_ofld_rxqs(adap, adap->sge.rdmaciqs, adap->sge.rdmaciq);


	for (i = 0; i < ARRAY_SIZE(adap->sge.ofldtxq); i++) {
		struct sge_ofld_txq *q = &adap->sge.ofldtxq[i];

		if (q->q.desc) {
			tasklet_kill(&q->qresume_tsk);
			t4_ofld_eq_free(adap, adap->mbox, adap->pf, 0,
					q->q.cntxt_id);
			free_tx_desc(adap, &q->q, q->q.in_use, false);
			kfree(q->q.sdesc);
			__skb_queue_purge(&q->sendq);
			free_txq(adap, &q->q);
		}
	}


	for (i = 0; i < ARRAY_SIZE(adap->sge.ctrlq); i++) {
		struct sge_ctrl_txq *cq = &adap->sge.ctrlq[i];

		if (cq->q.desc) {
			tasklet_kill(&cq->qresume_tsk);
			t4_ctrl_eq_free(adap, adap->mbox, adap->pf, 0,
					cq->q.cntxt_id);
			__skb_queue_purge(&cq->sendq);
			free_txq(adap, &cq->q);
		}
	}

	if (adap->sge.fw_evtq.desc)
		free_rspq_fl(adap, &adap->sge.fw_evtq, NULL);

	if (adap->sge.intrq.desc)
		free_rspq_fl(adap, &adap->sge.intrq, NULL);


	memset(adap->sge.egr_map, 0,
	       adap->sge.egr_sz * sizeof(*adap->sge.egr_map));
}
