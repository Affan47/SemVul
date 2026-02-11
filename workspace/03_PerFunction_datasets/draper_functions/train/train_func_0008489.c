seaudit_log_parse_line(seaudit_log_t * log, char *line)
{
	char *orig_line = NULL;
	seaudit_message_t *prev_message;
	seaudit_message_type_e is_sel, prev_message_type;
	apol_vector_t *tokens = NULL;
	int retval = -1, retval2, has_warnings = 0, error = 0;

	is_sel = is_selinux(line);
	if (log->next_line) {
		prev_message = apol_vector_get_element(log->messages, apol_vector_get_size(log->messages) - 1);
		seaudit_message_get_data(prev_message, &prev_message_type);
		if (!(is_sel == SEAUDIT_MESSAGE_TYPE_INVALID && prev_message_type == SEAUDIT_MESSAGE_TYPE_BOOL) &&
		    !(is_sel == SEAUDIT_MESSAGE_TYPE_LOAD && prev_message_type == SEAUDIT_MESSAGE_TYPE_LOAD)) {
			WARN(log, "%s", "Parser was in the middle of a line, but next message was not the correct format.");
			has_warnings = 1;
			log->next_line = 0;
		} else {
			is_sel = prev_message_type;
		}
	}
	if (is_sel == SEAUDIT_MESSAGE_TYPE_INVALID) {

		return 0;
	}

	if ((orig_line = strdup(line)) == NULL) {
		error = errno;
		ERR(log, "%s", strerror(error));
		goto cleanup;
	}
	if (get_tokens(log, line, &tokens) < 0) {
		error = errno;
		ERR(log, "%s", strerror(error));
		goto cleanup;
	}

	switch (is_sel) {
	case SEAUDIT_MESSAGE_TYPE_AVC:
		retval2 = avc_parse(log, tokens);
		break;
	case SEAUDIT_MESSAGE_TYPE_BOOL:
		retval2 = bool_parse(log, tokens);
		break;
	case SEAUDIT_MESSAGE_TYPE_LOAD:
		retval2 = load_parse(log, tokens);
		break;
	default:

		assert(0);
		errno = EINVAL;
		retval2 = -1;
	}
	if (retval2 < 0) {
		error = errno;
		ERR(log, "%s", strerror(error));
		goto cleanup;
	} else if (retval2 > 0) {
		if (apol_vector_append(log->malformed_msgs, orig_line) < 0) {
			error = errno;
			ERR(log, "%s", strerror(error));
			goto cleanup;
		}
		orig_line = NULL;
		has_warnings = 1;
	}

	retval = 0;
      cleanup:
	free(orig_line);
	apol_vector_destroy(&tokens);
	if (retval < 0) {
		errno = error;
		return -1;
	}
	return has_warnings;
}
