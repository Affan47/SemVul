recursive_scan_step_update_qrp(struct bgtask *bt, void *data, int ticks)
{
	struct recursive_scan *ctx = data;
	shared_file_t *sf;

	recursive_scan_check(ctx);

	ctx->ticks = 0;

	for (; UNSIGNED(ctx->idx) < files_scanned; ctx->idx++) {
		sf = sorted_file_table[ctx->idx];

		if (!sf)
			continue;

		if (ctx->ticks++ >= ticks)
			return BGR_MORE;

		shared_file_check(sf);
		qrp_add_file(sf, ctx->words);
	}

	while (NULL != (sf = slist_shift(ctx->partial_files))) {
		shared_file_check(sf);


		sf->file_index = files_scanned + (hset_count(partial_files) -
			slist_length(ctx->partial_files));

		qrp_add_file(sf, ctx->words);
		shared_file_unref(&sf);

		if (ctx->ticks++ >= ticks)
			return BGR_MORE;
	}

	bg_task_ticks_used(bt, ctx->ticks);
	return BGR_NEXT;
}
