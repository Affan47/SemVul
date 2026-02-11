pcierror_quiesce_device(struct octeon_device *oct)
{
	int i;


	force_io_queues_off(oct);


	schedule_timeout_uninterruptible(100);

	if (wait_for_pending_requests(oct))
		dev_err(&oct->pci_dev->dev, "There were pending requests\n");


	for (i = 0; i < MAX_OCTEON_INSTR_QUEUES; i++) {
		struct octeon_instr_queue *iq;

		if (!(oct->io_qmask.iq & (1UL << i)))
			continue;
		iq = oct->instr_queue[i];

		if (atomic_read(&iq->instr_pending)) {
			spin_lock_bh(&iq->lock);
			iq->fill_cnt = 0;
			iq->octeon_read_index = iq->host_write_index;
			iq->stats.instr_processed +=
				atomic_read(&iq->instr_pending);
			lio_process_iq_request_list(oct, iq);
			spin_unlock_bh(&iq->lock);
		}
	}


	lio_process_ordered_list(oct, 1);


}
