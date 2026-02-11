laptop_mode_timer_fn(unsigned long data)
{
	struct request_queue *q = (struct request_queue *)data;
	int nr_pages = global_page_state(NR_FILE_DIRTY) +
		global_page_state(NR_UNSTABLE_NFS);
	struct bdi_writeback *wb;


	if (!bdi_has_dirty_io(q->backing_dev_info))
		return;

	rcu_read_lock();
	list_for_each_entry_rcu(wb, &q->backing_dev_info->wb_list, bdi_node)
		if (wb_has_dirty_io(wb))
			wb_start_writeback(wb, nr_pages, true,
					   WB_REASON_LAPTOP_TIMER);
	rcu_read_unlock();
}
