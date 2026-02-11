init_once(void)
{
	if ((init_error = git_mutex_init(&git__mwindow_mutex)) != 0)
		return;
	pthread_key_create(&_tls_key, &cb__free_status);


	if ((init_error = git_hash_global_init()) >= 0)
		init_error = git_sysdir_global_init();


	init_ssl();

	GIT_MEMORY_BARRIER;
}
