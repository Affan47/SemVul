check_dead_children(void)
{
	unsigned spawned, reaped, deleted;

	spawned = children_spawned;
	reaped = children_reaped;
	deleted = children_deleted;

	while (deleted < reaped) {
		pid_t pid = dead_child[deleted % MAX_CHILDREN];
		const char *dead = pid < 0 ? " (with error)" : "";

		if (pid < 0)
			pid = -pid;


		if (verbose) {
			if (log_syslog)
				syslog(LOG_INFO, "[%d] Disconnected%s",
						pid, dead);
			else
				fprintf(stderr, "[%d] Disconnected%s\n",
						pid, dead);
		}
		remove_child(pid, deleted, spawned);
		deleted++;
	}
	children_deleted = deleted;
}
