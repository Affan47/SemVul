printtime(time_t t)
{
	struct tm *tmp;

	if (t == 0)
		return;

	tmp = gmtime(&t);

	fprintf(fdout, "%02d/%02d/%04d %02d:%02d:%02d",
		tmp->tm_mday, tmp->tm_mon + 1, tmp->tm_year + 1900,
		tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
}
