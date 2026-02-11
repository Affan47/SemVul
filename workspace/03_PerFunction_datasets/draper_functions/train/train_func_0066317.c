dispatch_task(struct link *mpi_link, struct mpi_queue_task *t, int timeout)
{
	struct mpi_queue_file *tf;
	int stoptime = time(0) + timeout;


	debug(D_MPI, "sending task %d\n", t->taskid);
	if(t->input_files) {
		list_first_item(t->input_files);
		while((tf = list_next_item(t->input_files))) {
			link_putfstring(mpi_link, "stat %d %s\n", stoptime, t->taskid, tf->name);
		}
	}

	t->start_time = timestamp_get();
	link_putfstring(mpi_link, "work %d %zu\n%s", stoptime, t->taskid, strlen(t->command_line), t->command_line);
	t->status = MPI_QUEUE_TASK_STATUS_EXECUTING;
	link_putfstring(mpi_link, "close %d\n", stoptime, t->taskid);

	debug(D_MPI, "'%s' sent as task %d", t->command_line, t->taskid);
	return 1;
}
