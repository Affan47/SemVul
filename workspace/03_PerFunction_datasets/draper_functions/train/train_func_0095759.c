dlm_num_locks_in_lockres(struct dlm_lock_resource *res)
{
	int total_locks = 0;
	struct list_head *iter, *queue = &res->granted;
	int i;

	for (i=0; i<3; i++) {
		list_for_each(iter, queue)
			total_locks++;
		queue++;
	}
	return total_locks;
}
