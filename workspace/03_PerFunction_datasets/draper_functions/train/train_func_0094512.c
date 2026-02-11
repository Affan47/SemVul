__plain_target_redirect(u32 tid, char *dest, u8 type, int update)
{
	struct target *target;
	char *a = dest, *p = dest + strlen(dest);

	if (!tid || !dest || !type)
		return -EINVAL;

	if (type != ISCSI_STATUS_TGT_MOVED_TEMP &&
			type != ISCSI_STATUS_TGT_MOVED_PERM)
		return -EINVAL;

	target = target_find_by_id(tid);
	if (!target) {
		log_error("can't find target: %d", tid);
		return -ENOENT;
	}

	while(isspace(*a))
		a++;

	if (strlen(a)) {
		while(isspace(*(--p)))
			*p = '\0';

		if ((p = strrchr(a, ']')))
			p = strchrnul(p, ':');
		else
			p = strchrnul(a, ':');

		if (*p) {
			*(p++) = '\0';
			if (!atoi(p))
				return -EINVAL;
		}

		if (!is_addr_valid(a))
			return -EINVAL;

		log_warning("target %s %s redirected to %s:%s", target->name,
			(type == ISCSI_STATUS_TGT_MOVED_TEMP) ? "temporarily" :
								"permanently",
						a, strlen(p) ? p : "3260");
	} else
		log_warning("target redirection for %s cleared", target->name);

	target->redirect.type = type;

	snprintf(target->redirect.addr, sizeof(target->redirect.addr), "%s", a);
	snprintf(target->redirect.port, sizeof(target->redirect.port), "%s", p);

	return 0;
}
