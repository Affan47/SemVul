track_move (uintptr_t src, uintptr_t dst)
{
	int i;
	for (i = 0; i < num_tracked_objects; ++i) {
		if (tracked_objects [i] == src)
			fprintf (outfile, "Object %p moved to %p\n", (void*)src, (void*)dst);
		else if (tracked_objects [i] == dst)
			fprintf (outfile, "Object %p moved from %p\n", (void*)dst, (void*)src);
	}
}
