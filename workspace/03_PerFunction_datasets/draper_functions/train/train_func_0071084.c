main(void) {
	Counter *c;
	long threads[THREADS];
	long i;

	gwlib_init();
	log_set_output_level(GW_INFO);
	c = counter_create();
	for (i = 0; i < THREADS; ++i)
		threads[i] = gwthread_create(check, c);
	for (i = 0; i < THREADS; ++i)
		gwthread_join(threads[i]);

	return 0;
}
