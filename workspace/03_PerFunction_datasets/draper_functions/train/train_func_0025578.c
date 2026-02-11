adjust_size(size_t requested, unsigned *hint_ptr, bool verbose)
{
	size_t rounded;
	size_t wasted;
	size_t size;
	size_t arena_size;
	unsigned hint = *hint_ptr;


	size = MAX(sizeof(char *), requested);


	size += OVH_LENGTH;

	size = zalloc_round(size);

	g_assert(size < MAX_ZONE_SIZE);


	hint = (hint == 0) ? DEFAULT_HINT : hint;
	if (hint > MAX_ZONE_SIZE / size) {
		hint = MAX_ZONE_SIZE / size;
	}
	arena_size = size * hint;
	g_assert(arena_size <= MAX_ZONE_SIZE);

	rounded = round_pagesize(arena_size);
	hint = rounded / size;
	wasted = rounded - size * hint;


	if (wasted > 0) {
		size_t bsize = rounded / hint;
		size_t adjusted = (bsize / ZALLOC_ALIGNBYTES) * ZALLOC_ALIGNBYTES;

		g_assert(adjusted >= size);

		if (adjusted != size) {
			if (zalloc_debugging(0) && verbose) {
				s_debug("ZALLOC adjusting block size from %zu to %zu "
					"(%u blocks will waste %zu bytes at end of "
					"%zu-byte subzone)",
					requested, adjusted, hint, rounded - hint * adjusted,
					rounded);
			}
		} else {
			if (zalloc_debugging(0) && verbose) {
				s_debug("ZALLOC cannot adjust block size of %zu "
					"(%u blocks will waste %zu bytes at end of "
					"%zu-byte subzone)",
					requested, hint, rounded - hint * adjusted, rounded);
			}
		}

		size = adjusted;
	}

	*hint_ptr = hint;
	return size;
}
