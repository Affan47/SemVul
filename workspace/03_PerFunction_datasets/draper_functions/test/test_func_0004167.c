main(int argc, char **argv)
{
    double teff1, teff2;
    long t1, t2, tm1, tm2;
    int t, i;
    int stat = 0;


    pthread_t thread_handle[MAX_THREADS];


    int thread_id[MAX_THREADS];

    void *retval;
    struct timeval tv;

    if (argc < 3) {
	printf("Fehlende Parameter!\n");
	printf("Benutzung: %s <Threads> <Dimension>\n", argv[0]);
	printf("z.B.: %s 4 500\n", argv[0]);
	exit(1);
    } else {
	threads = atoi(argv[1]);
	if (threads > MAX_THREADS) {
	    printf("zu viele Threads, verwende Maximalanzahl (%d)\n",
		   MAX_THREADS);
	    threads = MAX_THREADS;
	}
	size = atoi(argv[2]);
	if (size > MAX) {
	    printf("Zu gross, verwende Maximalwert (%d)\n", MAX);
	    size = MAX;
	} else
	    printf("Verwendete Dimension: %d\n", size);
    }

    printf("Erstelle zwei (%d x %d)-Matrizen\n", size, size);
    fflush(stdout);
    createmat();
    printf("Fertig. Bitte Taste druecken ...\n");
    t = getchar();


    for (i = 0; i < threads; i++) {
	thread_id[i] = i;
    }


    gettimeofday(&tv, NULL);
    t1 = tv.tv_sec;
    tm1 = tv.tv_usec;


    for (i = 0; i < threads; i++) {
	stat = stat
	    || pthread_create(&thread_handle[i], NULL, multiplythread,
			      &thread_id[i]);
    }
    if (stat) {
	fprintf(stderr, "%s: Probleme mit Threaderzeugung!\n", argv[0]);
	exit(1);
    }

    for (i = 0; i < threads; i++) {
	stat = stat || pthread_join(thread_handle[i], &retval);
    }
    if (stat) {
	fprintf(stderr, "%s: Konnte Threads nicht synchronisieren.\n",
		argv[0]);
	exit(1);
    }


    gettimeofday(&tv, NULL);
    t2 = tv.tv_sec;
    tm2 = tv.tv_usec;

    teff1 = t1 * 1e6 + tm1;
    teff2 = t2 * 1e6 + tm2;

    printf("Zeit fuer die Berechnung in Sekunden: %f\n",
	   (teff2 - teff1) / 1e6);

#if DEBUG == 1
    printf("Matrix A:\n");
    printmat(a);
    printf("Matrix B:\n");
    printmat(b);
    printf("Ergebnismatrix C:\n");
    printmat(c);
#endif
    return (0);
}
