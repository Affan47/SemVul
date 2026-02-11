log_init(void)
{
	unsigned i;

	for (i = 0; i < G_N_ELEMENTS(log_domains); i++) {
		g_log_set_handler(log_domains[i],
			G_LOG_FLAG_RECURSION | G_LOG_FLAG_FATAL |
			G_LOG_LEVEL_ERROR | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING |
			G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG,
			log_handler, NULL);
	}

	gl_log_set_handler(log_handler, NULL);

	logfile[LOG_STDOUT].f = stdout;
	logfile[LOG_STDOUT].fd = fileno(stdout);
	logfile[LOG_STDOUT].name = "out";
	logfile[LOG_STDOUT].otime = tm_time();

	logfile[LOG_STDERR].f = stderr;
	logfile[LOG_STDERR].fd = fileno(stderr);
	logfile[LOG_STDERR].name = "err";
	logfile[LOG_STDERR].otime = tm_time();

	(void) log_chunk();

	log_inited = TRUE;
}
