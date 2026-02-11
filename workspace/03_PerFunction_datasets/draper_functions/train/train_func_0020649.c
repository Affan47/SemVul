proc_fork_connector(struct task_struct *task)
{
	struct cn_msg *msg;
	struct proc_event *ev;
	__u8 buffer[CN_PROC_MSG_SIZE] __aligned(8);
	struct task_struct *parent;

	if (atomic_read(&proc_event_num_listeners) < 1)
		return;

	msg = buffer_to_cn_msg(buffer);
	ev = (struct proc_event *)msg->data;
	memset(&ev->event_data, 0, sizeof(ev->event_data));
	get_seq(&msg->seq, &ev->cpu);
	ev->timestamp_ns = ktime_get_ns();
	ev->what = PROC_EVENT_FORK;
	rcu_read_lock();
	parent = rcu_dereference(task->real_parent);
	ev->event_data.fork.parent_pid = parent->pid;
	ev->event_data.fork.parent_tgid = parent->tgid;
	rcu_read_unlock();
	ev->event_data.fork.child_pid = task->pid;
	ev->event_data.fork.child_tgid = task->tgid;

	memcpy(&msg->id, &cn_proc_event_id, sizeof(msg->id));
	msg->ack = 0;
	msg->len = sizeof(*ev);
	msg->flags = 0;

	cn_netlink_send(msg, 0, CN_IDX_PROC, GFP_KERNEL);
}
