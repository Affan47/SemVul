verify_free(struct verify **ptr)
{
	struct verify *ctx = *ptr;

	if (ptr) {
		verify_check(ctx);

		if (ctx->task) {
			bg_task_cancel(ctx->task);
			ctx->task = NULL;
		}
		if (VERIFY_INVALID != ctx->status) {
			verify_shutdown(ctx);
		}
		if (ctx->files_to_hash) {
			struct verify_file *item;

			while (NULL != (item = hash_list_shift(ctx->files_to_hash))) {
				item->callback(NULL, VERIFY_SHUTDOWN, item->user_data);
				verify_file_free(&item);
			}
			hash_list_free(&ctx->files_to_hash);
		}
		file_object_release(&ctx->file);
		HFREE_NULL(ctx->buffer);
		ctx->magic = 0;
		WFREE(ctx);
		*ptr = NULL;
	}
}
