check_period(const GTimeVal *tv1, const GTimeVal *tv2, glong sec)
{
	glong tv1_sec = tv1->tv_sec + sec;
	glong tv1_usec = tv1->tv_usec;
	glong tv2_sec = tv2->tv_sec;
	glong tv2_usec = tv2->tv_usec;

	if (tv1_sec == tv2_sec) {
		return (tv1_usec > tv2_usec);
	} else {
		return (tv1_sec > tv2_sec);
	}
}
