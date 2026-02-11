parallel_writer_single_reader (void)
{
	pthread_t a,b,c;
	int i, j, res = 0;

	mono_os_mutex_init (&global_mutex);
	hash = mono_conc_hashtable_new (NULL, NULL);

	pthread_create (&a, NULL, pw_sr_thread, GINT_TO_POINTER (1));
	pthread_create (&b, NULL, pw_sr_thread, GINT_TO_POINTER (2));
	pthread_create (&c, NULL, pw_sr_thread, GINT_TO_POINTER (3));

	pthread_join (a, NULL);
	pthread_join (b, NULL);
	pthread_join (c, NULL);

	for (i = 0; i < 1000; ++i) {
		for (j = 1; j < 4; ++j) {
			if (mono_conc_hashtable_lookup (hash, GINT_TO_POINTER (j * 1000 + i)) != GINT_TO_POINTER (i + 1)) {
				res = j + 1;
				goto done;
			}
		}
	}

done:
	mono_conc_hashtable_destroy (hash);
	mono_os_mutex_destroy (&global_mutex);
	if (res)
		printf ("PAR_WRITER_SINGLE_READER TEST FAILED %d\n", res);
	return res;
}
