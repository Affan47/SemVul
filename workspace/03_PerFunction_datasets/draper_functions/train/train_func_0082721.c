drmtest_progress(const char *header, uint64_t i, uint64_t total)
{
	if (i+1 >= total) {
		fprintf(stderr, "\r%s100%%\n", header);
		return;
	}


	if (i % (total / 200) == 0 || i+1 >= total) {
		fprintf(stderr, "\r%s%3llu%%", header,
			(long long unsigned) i * 100 / total);
	}
}
