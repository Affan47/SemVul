delayed_ack_enqueue(struct lease *lease)
{
	struct leasequeue *q;

	if (!write_lease(lease))
		return;
	if (free_ackqueue) {
	   	q = free_ackqueue;
		free_ackqueue = q->next;
	} else {
		q = ((struct leasequeue *)
			     dmalloc(sizeof(struct leasequeue), MDL));
		if (!q)
			log_fatal("delayed_ack_enqueue: no memory!");
	}
	memset(q, 0, sizeof *q);

	lease_reference(&q->lease, lease, MDL);
	q->next = ackqueue_head;
	ackqueue_head = q;
	if (!ackqueue_tail)
		ackqueue_tail = q;
	else
		q->next->prev = q;

	outstanding_acks++;
	if (outstanding_acks > max_outstanding_acks) {
		commit_leases();


		memset(&max_fsync, 0, sizeof(max_fsync));
		cancel_timeout(commit_leases_ackout, NULL);
	} else {
		struct timeval next_fsync;

		if (max_fsync.tv_sec == 0 && max_fsync.tv_usec == 0) {

			max_fsync.tv_sec = cur_tv.tv_sec + max_ack_delay_secs;
			max_fsync.tv_usec = cur_tv.tv_usec +
				max_ack_delay_usecs;

			if (max_fsync.tv_usec >= 1000000) {
				max_fsync.tv_sec++;
				max_fsync.tv_usec -= 1000000;
			}
		}


		next_fsync.tv_sec = cur_tv.tv_sec;
		next_fsync.tv_usec = cur_tv.tv_usec + min_ack_delay_usecs;
		if (next_fsync.tv_usec >= 1000000) {
			next_fsync.tv_sec++;
			next_fsync.tv_usec -= 1000000;
		}

		if ((next_fsync.tv_sec > max_fsync.tv_sec) ||
		    ((next_fsync.tv_sec == max_fsync.tv_sec) &&
		     (next_fsync.tv_usec > max_fsync.tv_usec))) {
			next_fsync.tv_sec = max_fsync.tv_sec;
			next_fsync.tv_usec = max_fsync.tv_usec;
		}

		add_timeout(&next_fsync, commit_leases_ackout, NULL,
			    (tvref_t) NULL, (tvunref_t) NULL);
	}
}
