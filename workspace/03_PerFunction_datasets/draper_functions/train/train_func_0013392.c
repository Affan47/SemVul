test_simplesignal_impl(int find_reorder)
{
	struct event ev;
	struct itimerval itv;

	evsignal_set(&ev, SIGALRM, signal_cb, &ev);
	evsignal_add(&ev, NULL);

	if (find_reorder) {
		evsignal_del(&ev);
		evsignal_add(&ev, NULL);
	}

	memset(&itv, 0, sizeof(itv));
	itv.it_value.tv_sec = 0;
	itv.it_value.tv_usec = 100000;
	if (setitimer(ITIMER_REAL, &itv, NULL) == -1)
		goto skip_simplesignal;

	event_dispatch();
 skip_simplesignal:
	if (evsignal_del(&ev) == -1)
		test_ok = 0;

	cleanup_test();
}
