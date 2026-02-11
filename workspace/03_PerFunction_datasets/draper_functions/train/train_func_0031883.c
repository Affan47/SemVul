mcast_init()
{
	struct thr_info *thr;

	thr = calloc(1, sizeof(*thr));
	if (!thr)
		quit(1, "Failed to calloc mcast thr");

	if (thr_info_create(thr, NULL, mcast_thread, thr))
		quit(1, "API mcast thread create failed");
}
