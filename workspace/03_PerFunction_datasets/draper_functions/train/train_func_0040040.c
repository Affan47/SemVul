verify_enqueue(struct verify *ctx, int high_priority,
	const char *pathname, filesize_t offset, filesize_t amount,
	verify_callback callback, void *user_data)
{
	struct verify_file *item;
	int inserted;

	verify_check(ctx);
	g_return_val_if_fail(ctx->files_to_hash, FALSE);

	g_return_val_if_fail(pathname, FALSE);
	g_return_val_if_fail(callback, FALSE);

	item = verify_file_new(pathname, offset, amount, callback, user_data);
	if (hash_list_contains(ctx->files_to_hash, item)) {
		if (high_priority) {
			hash_list_moveto_head(ctx->files_to_hash, item);
			inserted = FALSE;
		} else {
			inserted = TRUE;
		}
		verify_file_free(&item);
	} else {
		if (high_priority) {
			hash_list_prepend(ctx->files_to_hash, item);
		} else {
			hash_list_append(ctx->files_to_hash, item);
		}
		inserted = TRUE;
	}

	if (GNET_PROPERTY(verify_debug)) {
		g_debug("%s %s digest verification for %s",
			inserted ? "enqueued" : "already had queued",
			verify_hash_name(ctx), pathname);
	}

	verify_create_task(ctx);
	return inserted;
}
