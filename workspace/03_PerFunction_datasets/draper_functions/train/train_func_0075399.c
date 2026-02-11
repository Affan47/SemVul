time_greater(struct timeval a, struct timeval b)
{
	if (a.tv_sec > b.tv_sec)
		return true;
	else if (a.tv_sec < b.tv_sec)
		 return false;

	return a.tv_usec > b.tv_usec;
}
