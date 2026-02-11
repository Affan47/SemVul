log_new_fast(struct db *db, uint64_t log_number,
			 struct dir *log_dir, struct dir *index_dir,
			 struct bitmap *bitmap,
			 log_move_callback move_callback,
			 void *move_context,
			 struct frozen_list *frozen_list)
{
	struct log *log = _log_new(db, log_number, log_dir, index_dir,
				   move_callback, move_context, frozen_list);
	if (log == NULL) {
		return NULL;
	}
	char *idx_file = idx_filename(log_number);
	struct hashdir *hdsets = hashdir_new_load(db,
						  _log_move, log,
						  index_dir, idx_file,
						  bitmap,
						  frozen_list);
	if (hdsets == NULL) {
		log_warn(db, "Can't find index file \"%s\".", idx_file);
		log_free(log);
		return NULL;


	}

	void *ptr;
	struct hashdir_item hdi;
	hashdir_for_each(hdsets, ptr, hdi) {
		stddev_add(&log->used_size, hdi.size);
	}
	log->hashdir = hdsets;
	return log;
}
