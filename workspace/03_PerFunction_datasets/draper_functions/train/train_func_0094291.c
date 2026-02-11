__update_mqd(struct mqd_manager *mm, void *mqd,
			struct queue_properties *q, unsigned int mtype,
			unsigned int atc_bit)
{
	struct vi_mqd *m;

	BUG_ON(!mm || !q || !mqd);

	pr_debug("kfd: In func %s\n", __func__);

	m = get_mqd(mqd);

	m->cp_hqd_pq_control = 5 << CP_HQD_PQ_CONTROL__RPTR_BLOCK_SIZE__SHIFT |
			atc_bit << CP_HQD_PQ_CONTROL__PQ_ATC__SHIFT |
			mtype << CP_HQD_PQ_CONTROL__MTYPE__SHIFT;
	m->cp_hqd_pq_control |=
			ffs(q->queue_size / sizeof(unsigned int)) - 1 - 1;
	pr_debug("kfd: cp_hqd_pq_control 0x%x\n", m->cp_hqd_pq_control);

	m->cp_hqd_pq_base_lo = lower_32_bits((uint64_t)q->queue_address >> 8);
	m->cp_hqd_pq_base_hi = upper_32_bits((uint64_t)q->queue_address >> 8);

	m->cp_hqd_pq_rptr_report_addr_lo = lower_32_bits((uint64_t)q->read_ptr);
	m->cp_hqd_pq_rptr_report_addr_hi = upper_32_bits((uint64_t)q->read_ptr);

	m->cp_hqd_pq_doorbell_control =
		1 << CP_HQD_PQ_DOORBELL_CONTROL__DOORBELL_EN__SHIFT |
		q->doorbell_off <<
			CP_HQD_PQ_DOORBELL_CONTROL__DOORBELL_OFFSET__SHIFT;
	pr_debug("kfd: cp_hqd_pq_doorbell_control 0x%x\n",
			m->cp_hqd_pq_doorbell_control);

	m->cp_hqd_eop_control = atc_bit << CP_HQD_EOP_CONTROL__EOP_ATC__SHIFT |
			mtype << CP_HQD_EOP_CONTROL__MTYPE__SHIFT;

	m->cp_hqd_ib_control = atc_bit << CP_HQD_IB_CONTROL__IB_ATC__SHIFT |
			3 << CP_HQD_IB_CONTROL__MIN_IB_AVAIL_SIZE__SHIFT |
			mtype << CP_HQD_IB_CONTROL__MTYPE__SHIFT;

	m->cp_hqd_eop_control |=
		ffs(q->eop_ring_buffer_size / sizeof(unsigned int)) - 1 - 1;
	m->cp_hqd_eop_base_addr_lo =
			lower_32_bits(q->eop_ring_buffer_address >> 8);
	m->cp_hqd_eop_base_addr_hi =
			upper_32_bits(q->eop_ring_buffer_address >> 8);

	m->cp_hqd_iq_timer = atc_bit << CP_HQD_IQ_TIMER__IQ_ATC__SHIFT |
			mtype << CP_HQD_IQ_TIMER__MTYPE__SHIFT;

	m->cp_hqd_vmid = q->vmid;

	if (q->format == KFD_QUEUE_FORMAT_AQL) {
		m->cp_hqd_pq_control |= CP_HQD_PQ_CONTROL__NO_UPDATE_RPTR_MASK |
				2 << CP_HQD_PQ_CONTROL__SLOT_BASED_WPTR__SHIFT;
	}

	m->cp_hqd_active = 0;
	q->is_active = false;
	if (q->queue_size > 0 &&
			q->queue_address != 0 &&
			q->queue_percent > 0) {
		m->cp_hqd_active = 1;
		q->is_active = true;
	}

	return 0;
}
