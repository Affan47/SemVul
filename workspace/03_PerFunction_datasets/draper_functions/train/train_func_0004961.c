triton_queue_ctx(struct _triton_context_t *ctx)
{
	spin_lock(&threads_lock);
	ctx->pending = 1;
	if (ctx->thread || ctx->queued || ctx->init || ctx->need_free) {
		spin_unlock(&threads_lock);
		return 0;
	}

	if (list_empty(&sleep_threads) || need_config_reload || triton_stat.thread_active > thread_count ||
		(ctx->priority == 0 && triton_stat.thread_count > thread_count_max)) {
		if (ctx->priority)
			list_add(&ctx->entry2, &ctx_queue);
		else
			list_add_tail(&ctx->entry2, &ctx_queue);
		spin_unlock(&threads_lock);
		ctx->queued = 1;
		log_debug2("ctx %p: queued\n", ctx);
		__sync_add_and_fetch(&triton_stat.context_pending, 1);
		return 0;
	}

	ctx->thread = list_entry(sleep_threads.next, typeof(*ctx->thread), entry2);
	ctx->thread->ctx = ctx;
	log_debug2("ctx %p: assigned to thread %p\n", ctx, ctx->thread);
	list_del(&ctx->thread->entry2);
	spin_unlock(&threads_lock);

	return 1;
}
