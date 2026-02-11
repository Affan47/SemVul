ignore_task_cpu(void *data)
{
	struct trace_array *tr = data;
	struct trace_pid_list *pid_list;


	pid_list = rcu_dereference_protected(tr->filtered_pids,
					     mutex_is_locked(&event_mutex));

	this_cpu_write(tr->trace_buffer.data->ignore_pid,
		       check_ignore_pid(pid_list, current));
}
