fz_lock_debug_unlock(fz_context *ctx, int lock)
{
	int idx = find_context(ctx);
	if (idx < 0)
		return;

	if (fz_locks_debug[idx][lock] == 0)
	{
		fprintf(stderr, "Attempt to release lock %d when not held!\n", lock);
	}
	fz_locks_debug[idx][lock] = 0;
}
