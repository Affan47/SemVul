nlm4svc_callback_exit(struct rpc_task *task, void *data)
{
	dprintk("lockd: %5u callback returned %d\n", task->tk_pid,
			-task->tk_status);
}
