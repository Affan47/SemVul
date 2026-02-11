ring_tx_db(struct adapter *adapter, struct sge_txq *tq,
			      int n)
{


	wmb();


	if (unlikely(tq->bar2_addr == NULL)) {
		u32 val = PIDX_V(n);

		t4_write_reg(adapter, T4VF_SGE_BASE_ADDR + SGE_VF_KDOORBELL,
			     QID_V(tq->cntxt_id) | val);
	} else {
		u32 val = PIDX_T5_V(n);


		WARN_ON(val & DBPRIO_F);


		if (n == 1 && tq->bar2_qid == 0) {
			unsigned int index = (tq->pidx
					      ? (tq->pidx - 1)
					      : (tq->size - 1));
			__be64 *src = (__be64 *)&tq->desc[index];
			__be64 __iomem *dst = (__be64 __iomem *)(tq->bar2_addr +
							 SGE_UDB_WCDOORBELL);
			unsigned int count = EQ_UNIT / sizeof(__be64);


			while (count) {


				writeq((__force u64)*src, dst);
				src++;
				dst++;
				count--;
			}
		} else
			writel(val | QID_V(tq->bar2_qid),
			       tq->bar2_addr + SGE_UDB_KDOORBELL);


		wmb();
	}
}
