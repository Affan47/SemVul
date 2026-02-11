time_inc(struct timeval addend, double increment)
{
	struct timeval newtime;

	newtime.tv_sec = addend.tv_sec + (int)increment;
	newtime.tv_usec = addend.tv_usec + (increment - (int)increment) * 1E6;


	if (newtime.tv_usec < 0) {
		newtime.tv_usec += 1E6;
		newtime.tv_sec -= 1;
	} else if (newtime.tv_usec >= 1E6) {
		newtime.tv_usec -= 1E6;
		newtime.tv_sec += 1;
	}
	return newtime;
}
