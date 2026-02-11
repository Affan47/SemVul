start_synaescope(void)
{
	if (pthread_mutex_trylock(&synaescope_mutex) != 0) {
		printf("synaescope already running\n");
		return;
	}
	if (!is_init) {
		is_init = 1;
		scope_win = init_synaescope_window();
	}
	gtk_widget_show(scope_win);
	pthread_create(&synaescope_thread, NULL, (void * (*)(void *))run_synaescope, NULL);
}
