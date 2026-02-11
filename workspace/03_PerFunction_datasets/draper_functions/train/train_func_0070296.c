_free_incoming_msg(struct io_buf *msg, slurmd_job_t *job)
{
	msg->ref_count--;
	if (msg->ref_count == 0) {

		list_enqueue(job->free_incoming, msg);


		eio_signal_wakeup(job->eio);
	}
}
