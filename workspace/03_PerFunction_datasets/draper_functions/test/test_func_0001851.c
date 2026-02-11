x3270_exit(int n)
{
	static Boolean already_exiting = 0;


	if (already_exiting)
		return;
	already_exiting = True;


	shutdown_toggles();


	host_disconnect(False);


	st_changed(ST_EXITING, True);

#if defined(WC3270)
	if (n) {
		char buf[2];

		printf("\n[Press <Enter>] ");
		fflush(stdout);
		(void) fgets(buf, sizeof(buf), stdin);

	}
#endif

	exit(n);
}
