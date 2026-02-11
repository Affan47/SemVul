dowait(int *statusp) {
	int n;
	interrupted = FALSE;
	if (!setjmp(slowlabel)) {
		slow = TRUE;
		n = interrupted ? -2 :
#if HAVE_WAIT3
			wait3((void *) statusp, 0, &wait_rusage);
#else
			wait((void *) statusp);
#endif
	} else
		n = -2;
	slow = FALSE;
	if (n == -2) {
		errno = EINTR;
		n = -1;
	}
	return n;
}
