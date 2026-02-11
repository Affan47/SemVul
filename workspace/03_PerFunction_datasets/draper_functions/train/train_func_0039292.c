fz_print_store(fz_context *ctx, FILE *out)
{
	fz_item *item, *next;
	fz_store *store = ctx->store;

	fprintf(out, "-- resource store contents --\n");

	fz_lock(ctx, FZ_LOCK_ALLOC);
	for (item = store->head; item; item = next)
	{
		next = item->next;
		if (next)
			next->val->refs++;
		fprintf(out, "store[*][refs=%d][size=%d] ", item->val->refs, item->size);
		fz_unlock(ctx, FZ_LOCK_ALLOC);
		item->type->debug(item->key);
		fprintf(out, " = %p\n", item->val);
		fz_lock(ctx, FZ_LOCK_ALLOC);
		if (next)
			next->val->refs--;
	}
	fz_unlock(ctx, FZ_LOCK_ALLOC);
}
