beiscsi_process_mcc_isr(struct beiscsi_hba *phba)
{
	struct be_queue_info *mcc_cq;
	struct  be_mcc_compl *mcc_compl;
	unsigned int num_processed = 0;

	mcc_cq = &phba->ctrl.mcc_obj.cq;
	mcc_compl = queue_tail_node(mcc_cq);
	mcc_compl->flags = le32_to_cpu(mcc_compl->flags);
	while (mcc_compl->flags & CQE_FLAGS_VALID_MASK) {

		if (num_processed >= 32) {
			hwi_ring_cq_db(phba, mcc_cq->id,
					num_processed, 0, 0);
			num_processed = 0;
		}
		if (mcc_compl->flags & CQE_FLAGS_ASYNC_MASK) {

			if (is_link_state_evt(mcc_compl->flags))

				beiscsi_async_link_state_process(phba,
				(struct be_async_event_link_state *) mcc_compl);
			else {
				beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_MBOX,
					    "BM_%d :  Unsupported Async Event, flags"
					    " = 0x%08x\n",
					    mcc_compl->flags);
				if (phba->state & BE_ADAPTER_LINK_UP) {
					phba->state |= BE_ADAPTER_CHECK_BOOT;
					phba->get_boot = BE_GET_BOOT_RETRIES;
				}
			}
		} else if (mcc_compl->flags & CQE_FLAGS_COMPLETED_MASK) {
			be_mcc_compl_process_isr(&phba->ctrl, mcc_compl);
			atomic_dec(&phba->ctrl.mcc_obj.q.used);
		}

		mcc_compl->flags = 0;
		queue_tail_inc(mcc_cq);
		mcc_compl = queue_tail_node(mcc_cq);
		mcc_compl->flags = le32_to_cpu(mcc_compl->flags);
		num_processed++;
	}

	if (num_processed > 0)
		hwi_ring_cq_db(phba, mcc_cq->id, num_processed, 1, 0);

}
