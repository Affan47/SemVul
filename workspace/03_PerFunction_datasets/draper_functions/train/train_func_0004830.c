fz_free_path(fz_context *ctx, fz_path *path)
{
	if (path == NULL)
		return;
	fz_free(ctx, path->items);
	fz_free(ctx, path);
}
