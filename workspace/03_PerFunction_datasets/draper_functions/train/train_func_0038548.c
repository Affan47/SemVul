fz_keep_storable(fz_context *ctx, fz_storable *s)
{
	if (s == NULL)
		return NULL;
	fz_lock(ctx, FZ_LOCK_ALLOC);
	if (s->refs > 0)
		s->refs++;
	fz_unlock(ctx, FZ_LOCK_ALLOC);
	return s;
}
