hdhomerun_debug_set_filename(struct hdhomerun_debug_t *dbg, const char *filename)
{
	if (!dbg) {
		return;
	}

	pthread_mutex_lock(&dbg->send_lock);

	if (!filename && !dbg->file_name) {
		pthread_mutex_unlock(&dbg->send_lock);
		return;
	}
	if (filename && dbg->file_name) {
		if (strcmp(filename, dbg->file_name) == 0) {
			pthread_mutex_unlock(&dbg->send_lock);
			return;
		}
	}

	hdhomerun_debug_close_internal(dbg);
	dbg->connect_delay = 0;

	if (dbg->file_name) {
		free(dbg->file_name);
		dbg->file_name = NULL;
	}
	if (filename) {
		dbg->file_name = strdup(filename);
	}

	pthread_mutex_unlock(&dbg->send_lock);
}
