testsuite_init (int argc, char **argv)
{
	int i, j;

	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-' && argv[i][1] != '-') {
			for (j = 1; argv[i][j]; j++) {
				if (argv[i][j] == 'v')
					verbose++;
			}
		}
	}

#ifdef ENABLE_THREADS
	pthread_key_create (&key, key_data_destroy);
#endif
}
