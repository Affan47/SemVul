fini_logger(int type)
{
	pthread_mutex_lock(&main_log.lock);

	if (main_log.fp != NULL) {
		fclose(main_log.fp);
		main_log.fp = NULL;

		if (opt.debug == DEBUG_ON) {
			printf("Closed logger\n");
			fflush(stdout);
		}
	}

	if (type == SHUTDOWN_LOGGER) {
		if ((main_log.log_file != NULL) &&
		    (main_log.log_file != default_logger_filename)) {
			free(main_log.log_file);
			main_log.log_file = NULL;
		}
	}

	main_log.enabled = LOGGER_DISABLED;

	pthread_mutex_unlock(&main_log.lock);
}
