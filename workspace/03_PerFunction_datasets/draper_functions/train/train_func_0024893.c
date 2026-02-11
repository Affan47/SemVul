timeit(
	void (*f)(void *, sha1_t *, size_t),
	void *o, sha1_t *keys, size_t count, size_t iter, const char *what,
	bool verbose)
{
	size_t i;
	tm_t start, end;
	double elapsed;

	tm_now_exact(&start);
	for (i = 0; i < iter; i++)
		(*f)(o, keys, count);
	tm_now_exact(&end);
	elapsed = tm_elapsed_f(&end, &start);

	if (verbose)
		g_debug("%s (%zu items, %zu loop%s): %F s (average: %F s)", what,
			count, iter, iter == 1 ? "" : "s", elapsed, elapsed / iter);

	return elapsed;
}
