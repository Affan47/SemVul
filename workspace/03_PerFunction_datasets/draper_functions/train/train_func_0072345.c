scavenge(fz_context *ctx, unsigned int tofree)
{
	fz_store *store = ctx->store;
	unsigned int count = 0;
	fz_item *item, *prev;


	for (item = store->tail; item; item = prev)
	{
		prev = item->prev;
		if (item->val->refs == 1)
		{

			count += item->size;
			evict(ctx, item);

			if (count >= tofree)
				break;


			prev = store->tail;
		}
	}

	return count != 0;
}
