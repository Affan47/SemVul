cdash_enlapsed_time(time_t t1, time_t t2) {
	double diff;

	diff = difftime(t2, t1);
	return (diff == 0 ? 0 : (diff / 60));
}
