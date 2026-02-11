update_mqd(struct mqd_manager *mm, void *mqd,
			struct queue_properties *q)
{
	struct cik_mqd *m;

	BUG_ON(!mm || !q || !mqd);

	pr_debug("kfd: In func %s\n", __func__);

	m = get_mqd(mqd);
	m->cp_hqd_pq_control = DEFAULT_RPTR_BLOCK_SIZE |
				DEFAULT_MIN_AVAIL_SIZE | PQ_ATC_EN;


	m->cp_hqd_pq_control |= ffs(q->queue_size / sizeof(unsigned int))
								- 1 - 1;
	m->cp_hqd_pq_base_lo = lower_32_bits((uint64_t)q->queue_address >> 8);
	m->cp_hqd_pq_base_hi = upper_32_bits((uint64_t)q->queue_address >> 8);
	m->cp_hqd_pq_rptr_report_addr_lo = lower_32_bits((uint64_t)q->read_ptr);
	m->cp_hqd_pq_rptr_report_addr_hi = upper_32_bits((uint64_t)q->read_ptr);
	m->cp_hqd_pq_doorbell_control = DOORBELL_EN |
					DOORBELL_OFFSET(q->doorbell_off);

	m->cp_hqd_vmid = q->vmid;

	if (q->format == KFD_QUEUE_FORMAT_AQL) {
		m->cp_hqd_pq_control |= NO_UPDATE_RPTR;
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
