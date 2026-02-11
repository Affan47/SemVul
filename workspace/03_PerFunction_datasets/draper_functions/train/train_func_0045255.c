base_free(struct base *base)
{
	logs_iterate(base->logs, _save_log, base);

	while (logs_oldest(base->logs)) {
		struct log *log = logs_oldest(base->logs);
		logs_del(base->logs, log);
		log_free(log);
	}
	frozen_list_free(base->frozen_list);

	if (base->writer) {
		writer_free(base->writer);
	}
	itree_free(base->itree);
	logs_free(base->logs);
	free(base);
}
