mpi_queue_submit(struct mpi_queue *q, struct mpi_queue_task *t)
{

	static int next_taskid = 1;

	if(t->output) {
		free(t->output);
		t->output = 0;
	}
	t->status = MPI_QUEUE_TASK_STATUS_READY;
	t->total_transfer_time = 0;
	t->result = MPI_QUEUE_RESULT_UNSET;


	t->taskid = next_taskid++;


	list_push_tail(q->ready_list, t);
	t->submit_time = timestamp_get();
	q->total_tasks_submitted++;

	return (t->taskid);
}
