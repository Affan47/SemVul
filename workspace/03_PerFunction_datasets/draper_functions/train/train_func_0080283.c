seccomp_action_logged_from_name(u32 *action_logged,
					    const char *name)
{
	const struct seccomp_log_name *cur;

	for (cur = seccomp_log_names; cur->name; cur++) {
		if (!strcmp(cur->name, name)) {
			*action_logged = cur->log;
			return true;
		}
	}

	return false;
}
