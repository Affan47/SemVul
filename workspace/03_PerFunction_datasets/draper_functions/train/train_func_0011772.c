_fiu_init_final(void)
{
	struct timeval tv;

	rec_inc();

	fiu_init(0);


	gettimeofday(&tv, NULL);
	srandom(tv.tv_usec);

	rec_dec();
}
