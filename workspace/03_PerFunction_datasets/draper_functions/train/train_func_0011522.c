create_monitor(pthread_t *tid, char *dir_path, int flags,
	notifier_t *notifier)
{
	mon_params_t *m_param;

	if ((m_param = malloc(sizeof *m_param)) == NULL) {
		perror("malloc()");
		return;
	}


	m_param->flags = flags;
	strncpy(m_param->dir_path, dir_path, sizeof m_param->dir_path);
	m_param->notifier = notifier;


	pthread_create(tid, NULL, monitor, (void *)m_param);
}
