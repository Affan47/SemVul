ena_com_aenq_intr_handler(struct ena_com_dev *dev, void *data)
{
	struct ena_admin_aenq_entry *aenq_e;
	struct ena_admin_aenq_common_desc *aenq_common;
	struct ena_com_aenq *aenq  = &dev->aenq;
	ena_aenq_handler handler_cb;
	u16 masked_head, processed = 0;
	u8 phase;

	masked_head = aenq->head & (aenq->q_depth - 1);
	phase = aenq->phase;
	aenq_e = &aenq->entries[masked_head];
	aenq_common = &aenq_e->aenq_common_desc;


	while ((aenq_common->flags & ENA_ADMIN_AENQ_COMMON_DESC_PHASE_MASK) ==
	       phase) {
		pr_debug("AENQ! Group[%x] Syndrom[%x] timestamp: [%llus]\n",
			 aenq_common->group, aenq_common->syndrom,
			 (u64)aenq_common->timestamp_low +
				 ((u64)aenq_common->timestamp_high << 32));


		handler_cb = ena_com_get_specific_aenq_cb(dev,
							  aenq_common->group);
		handler_cb(data, aenq_e);


		masked_head++;
		processed++;

		if (unlikely(masked_head == aenq->q_depth)) {
			masked_head = 0;
			phase = !phase;
		}
		aenq_e = &aenq->entries[masked_head];
		aenq_common = &aenq_e->aenq_common_desc;
	}

	aenq->head += processed;
	aenq->phase = phase;


	if (!processed)
		return;


	mb();
	writel((u32)aenq->head, dev->reg_bar + ENA_REGS_AENQ_HEAD_DB_OFF);
}
