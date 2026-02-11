__timeout_millisec(const struct timeval *now, const struct timeval *expires)
{
	struct timeval	__now, delta = { 0, 0 };

	if (now == NULL) {
		gettimeofday(&__now, NULL);
		now = &__now;
	}

	timersub(expires, now, &delta);

	return delta.tv_sec * 1000 + delta.tv_usec / 1000;
}
