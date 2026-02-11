nes_clean_cq(struct nes_qp *nesqp, struct nes_cq *nescq)
{
	u32 cq_head;
	u32 lo;
	u32 hi;
	u64 u64temp;
	unsigned long flags = 0;

	spin_lock_irqsave(&nescq->lock, flags);

	cq_head = nescq->hw_cq.cq_head;
	while (le32_to_cpu(nescq->hw_cq.cq_vbase[cq_head].cqe_words[NES_CQE_OPCODE_IDX]) & NES_CQE_VALID) {
		rmb();
		lo = le32_to_cpu(nescq->hw_cq.cq_vbase[cq_head].cqe_words[NES_CQE_COMP_COMP_CTX_LOW_IDX]);
		hi = le32_to_cpu(nescq->hw_cq.cq_vbase[cq_head].cqe_words[NES_CQE_COMP_COMP_CTX_HIGH_IDX]);
		u64temp = (((u64)hi) << 32) | ((u64)lo);
		u64temp &= ~(NES_SW_CONTEXT_ALIGN-1);
		if (u64temp == (u64)(unsigned long)nesqp) {

			nescq->hw_cq.cq_vbase[cq_head].cqe_words[NES_CQE_COMP_COMP_CTX_LOW_IDX] = 0;
			nescq->hw_cq.cq_vbase[cq_head].cqe_words[NES_CQE_COMP_COMP_CTX_HIGH_IDX] = 0;
		}

		if (++cq_head >= nescq->hw_cq.cq_size)
			cq_head = 0;
	}

	spin_unlock_irqrestore(&nescq->lock, flags);
}
