tm_cputime(double *user, double *sys)
{
	static bool getrusage_failed;
	double u;
	double s;

	if (!getrusage_failed) {
#if defined(HAS_GETRUSAGE)
		struct rusage usage;

		errno = ENOTSUP;
		if G_UNLIKELY(-1 == getrusage(RUSAGE_SELF, &usage)) {
			u = 0;
			s = 0;
			g_warning("getrusage(RUSAGE_SELF, ...) failed: %m");
		} else {
			u = tm2f(&usage.ru_utime);
			s = tm2f(&usage.ru_stime);
		}
#else
		getrusage_failed = TRUE;
#endif
	} else {

		u = 0;
		s = 0;
	}

	if (getrusage_failed) {
#if defined(HAS_TIMES)
		struct tms t;

		(void) times(&t);

		u = (double) t.tms_utime / (double) clock_hz();
		s = (double) t.tms_stime / (double) clock_hz();
#else
		static bool warned = FALSE;

		if (!warned) {
			g_warning("getrusage() is unusable and times() is missing");
			g_warning("will be unable to monitor CPU usage; using wall clock.");
			warned = TRUE;
		}

		u = (double) tm_time_exact();
		s = 0.0;
#endif
	}

	if (user) *user = u;
	if (sys)  *sys  = s;

	return u + s;
}
