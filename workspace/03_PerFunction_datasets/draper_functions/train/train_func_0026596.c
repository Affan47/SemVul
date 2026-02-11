_log_new(struct db *db, uint64_t log_number,
			    struct dir *log_dir, struct dir *index_dir,
			    log_move_callback move_callback,
			    void *move_userdata,
			    struct frozen_list *frozen_list)
{
	struct reader *reader = reader_new(db, log_dir, log_filename(log_number));
	if (reader == NULL) {
		return NULL;
	}

	struct log *log = malloc(sizeof(struct log));
	memset(log, 0, sizeof(struct log));
	log->db = db;
	log->log_dir = log_dir;
	log->index_dir = index_dir;
	log->log_number = log_number;
	log->reader = reader;

	log->move_callback = move_callback;
	log->move_userdata = move_userdata;

	log->frozen_list = frozen_list;
	return log;
}
