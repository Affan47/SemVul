plain_target_init(FILE *fp)
{
	char buf[BUFSIZE];
	char *p, *q;
	int idx;
	u32 tid, val;

	tid = 0;
	while (fgets(buf, BUFSIZE, fp)) {
		q = buf;
		p = target_sep_string(&q);
		if (!p || *p == '#')
			continue;
		if (!strcasecmp(p, "Target")) {
			tid = 0;
			if (!(p = target_sep_string(&q)))
				continue;
			__plain_target_create(&tid, p, 0);
		} else if (!strcasecmp(p, "Alias") && tid) {
			;
		} else if (!strcasecmp(p, "MaxSessions") && tid) {
			struct target * const target =
				target_find_by_id(tid);
			if (target)
				target->max_nr_sessions = strtol(q, &q, 0);
			else
				log_warning("Target '%s' not found", q);
		} else if (!strcasecmp(p, "Lun") && tid) {
			u32 lun = strtol(q, &q, 10);
			__plain_lunit_create(tid, lun, q, 0);
		} else if (!((idx = param_index_by_name(p, target_keys)) < 0) && tid) {
			val = strtol(q, &q, 0);
			if (param_check_val(target_keys, idx, &val) < 0)
				log_warning("%s, %u\n", target_keys[idx].name, val);
			iscsi_param_partial_set(tid, 0, key_target, idx, val);
		} else if (!((idx = param_index_by_name(p, session_keys)) < 0) && tid) {
			char *str = target_sep_string(&q);
			if (param_str_to_val(session_keys, idx, str, &val) < 0)
				continue;
			if (param_check_val(session_keys, idx, &val) < 0)
				log_warning("%s, %u\n", session_keys[idx].name, val);
			iscsi_param_partial_set(tid, 0, key_session, idx, val);
		}
	}

	return;
}
