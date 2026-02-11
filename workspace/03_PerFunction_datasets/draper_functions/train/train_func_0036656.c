ima_measurements_next(struct seq_file *m, void *v, loff_t *pos)
{
	struct ima_queue_entry *qe = v;


	rcu_read_lock();
	qe = list_entry_rcu(qe->later.next, struct ima_queue_entry, later);
	rcu_read_unlock();
	(*pos)++;

	return (&qe->later == &ima_measurements) ? NULL : qe;
}
