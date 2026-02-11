myrand(int down, int up)
{
	struct timeval tv;
	if (!isseed) {
		gettimeofday(&tv, 0);
		srand(tv.tv_sec);
		isseed = 1;
	}
	return ( down + ( rand() % (up - down + 1) ) );
}
