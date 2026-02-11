shift_logs(struct auditd_consumer_data *data)
{


	unsigned int num_logs, len;
	char *name;

	len = strlen(data->config->log_file) + 16;
	name = (char *)malloc(len);
	if (name == NULL) {
		audit_msg(LOG_ERR, "No memory shifting logs");
		return;
	}


	num_logs = last_log;
	while (num_logs) {
		snprintf(name, len, "%s.%d", data->config->log_file,
						num_logs);
		if (access(name, R_OK) != 0)
			break;
		num_logs++;
	}


	if (num_logs <= last_log && last_log > 1) {
		audit_msg(LOG_WARNING, "Last known log disappeared (%s)", name);
		num_logs = last_log = 1;
		while (num_logs) {
			snprintf(name, len, "%s.%d", data->config->log_file,
							num_logs);
			if (access(name, R_OK) != 0)
				break;
			num_logs++;
		}
		audit_msg(LOG_INFO, "Next log to use will be %s", name);
	}
	last_log = num_logs;
	rotate_logs(data, num_logs+1);
	free(name);
}
