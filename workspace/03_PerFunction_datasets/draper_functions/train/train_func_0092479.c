dpado_check_next(int conn_cnt)
{
	pthread_mutex_lock(&dpado_range_lock);
	if (dpado_range_next && conn_cnt == dpado_range_next->conn_cnt) {
		pado_delay = dpado_range_next->pado_delay;
		dpado_range_prev = dpado_range_next;
		if (dpado_range_next->entry.next != &dpado_range_list)
			dpado_range_next = list_entry(dpado_range_next->entry.next, typeof(*dpado_range_next), entry);
		else
			dpado_range_next = NULL;


	}
	pthread_mutex_unlock(&dpado_range_lock);
}
