process_intrq(struct adapter *adapter)
{
	struct sge *s = &adapter->sge;
	struct sge_rspq *intrq = &s->intrq;
	unsigned int work_done;
	u32 val;

	spin_lock(&adapter->sge.intrq_lock);
	for (work_done = 0; ; work_done++) {
		const struct rsp_ctrl *rc;
		unsigned int qid, iq_idx;
		struct sge_rspq *rspq;


		rc = (void *)intrq->cur_desc + (intrq->iqe_len - sizeof(*rc));
		if (!is_new_response(rc, intrq))
			break;


		dma_rmb();
		if (unlikely(RSPD_TYPE_G(rc->type_gen) != RSPD_TYPE_INTR_X)) {
			dev_err(adapter->pdev_dev,
				"Unexpected INTRQ response type %d\n",
				RSPD_TYPE_G(rc->type_gen));
			continue;
		}


		qid = RSPD_QID_G(be32_to_cpu(rc->pldbuflen_qid));
		iq_idx = IQ_IDX(s, qid);
		if (unlikely(iq_idx >= MAX_INGQ)) {
			dev_err(adapter->pdev_dev,
				"Ingress QID %d out of range\n", qid);
			continue;
		}
		rspq = s->ingr_map[iq_idx];
		if (unlikely(rspq == NULL)) {
			dev_err(adapter->pdev_dev,
				"Ingress QID %d RSPQ=NULL\n", qid);
			continue;
		}
		if (unlikely(rspq->abs_id != qid)) {
			dev_err(adapter->pdev_dev,
				"Ingress QID %d refers to RSPQ %d\n",
				qid, rspq->abs_id);
			continue;
		}


		napi_schedule(&rspq->napi);
		rspq_next(intrq);
	}

	val = CIDXINC_V(work_done) | SEINTARM_V(intrq->intr_params);


	if (unlikely(!intrq->bar2_addr)) {
		t4_write_reg(adapter, T4VF_SGE_BASE_ADDR + SGE_VF_GTS,
			     val | INGRESSQID_V(intrq->cntxt_id));
	} else {
		writel(val | INGRESSQID_V(intrq->bar2_qid),
		       intrq->bar2_addr + SGE_UDB_GTS);
		wmb();
	}

	spin_unlock(&adapter->sge.intrq_lock);

	return work_done;
}
