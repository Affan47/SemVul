base_schedule_snapshot(struct base *base)
{
	if (base->snapshot_child_pid == -1) {
		return _base_save_state(base);
	}
	if (base->snapshot_child_pid == 0) {
		base->snapshot_child_pid = sys_fork(_do_snapshot, base);
		return base->snapshot_child_pid == -1 ? -1 : 0;
	}

	if (sys_pid_exist(base->snapshot_child_pid) == 0) {
		base->snapshot_child_pid = sys_fork(_do_snapshot, base);
		return base->snapshot_child_pid == -1 ? -1 : 0;
	}
	return -2;
}
