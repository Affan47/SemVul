parse_trgt_params(struct msg_trgt *msg, char *params)
{
	char *p, *q;

	while ((p = strsep(&params, ",")) != NULL) {
		int idx;
		u32 val;
		if (!*p)
			continue;
		if (!(q = strchr(p, '=')))
			continue;
		*q++ = '\0';

		if (!((idx = param_index_by_name(p, target_keys)) < 0)) {
			if (param_str_to_val(target_keys, idx, q, &val)) {
				fprintf(stderr,
					"Invalid %s value \"%s\".\n",
					target_keys[idx].name, q);
				return -EINVAL;
			}
			if (!param_check_val(target_keys, idx, &val))
				msg->target_partial |= (1 << idx);
			msg->target_param[idx].val = val;
			msg->type |= 1 << key_target;

			continue;
		}

		if (!((idx = param_index_by_name(p, session_keys)) < 0)) {
			if (param_str_to_val(session_keys, idx, q, &val)) {
				fprintf(stderr,
					"Invalid %s value \"%s\".\n",
					session_keys[idx].name, q);
				return -EINVAL;
			}
			if (!param_check_val(session_keys, idx, &val))
				msg->session_partial |= (1 << idx);
			msg->session_param[idx].val = val;
			msg->type |= 1 << key_session;

			continue;
		}
		fprintf(stderr, "Unknown parameter \"%s\".\n", p);
		return -EINVAL;
	}

	return 0;
}
