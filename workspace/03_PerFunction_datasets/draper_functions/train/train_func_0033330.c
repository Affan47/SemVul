seam_paral(long int diff) {
	diff = labs(diff);

	const int T = 5;

	pthread_t accuth, diffth[T];

	pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

	int p = 0;
	struct sync_s sync = {&p, &m};
	struct dtid_s dtid[T];

	sc_seam_paral_init();

	for (long int d = 0; d < diff; d++) {
		p = 0;

		pthread_create(&accuth, (pthread_attr_t*)NULL, seam_paral_accu, &sync);
		const int P = sc_seam_paral_start(0x40000, T);

		while (p < P) {
			for (int t = 0; t < T; t++) {
				dtid[t].p = p;
				dtid[t].t = t;
				pthread_create(&diffth[t], (pthread_attr_t*)NULL, seam_paral_diff_part, &dtid[t]);
			}
			for (int t = 0; t < T; t++)
				pthread_join(diffth[t], (void*)NULL);

			p++;
			pthread_mutex_unlock(&m);
		}

		pthread_join(accuth, (void*)NULL);

		sc_seam_paral_finish();

	}
	sc_seam_paral_close();
	pthread_mutex_destroy(&m);
}
