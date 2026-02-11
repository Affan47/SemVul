fz_store_item(fz_context *ctx, void *key, void *val_, unsigned int itemsize, fz_store_type *type)
{
	fz_item *item = NULL;
	unsigned int size;
	fz_storable *val = (fz_storable *)val_;
	fz_store *store = ctx->store;
	fz_store_hash hash = { NULL };
	int use_hash = 0;

	if (!store)
		return NULL;

	fz_var(item);


	fz_try(ctx)
	{
		item = fz_malloc_struct(ctx, fz_item);
	}
	fz_catch(ctx)
	{
		return NULL;
	}

	if (type->make_hash_key)
	{
		hash.free = val->free;
		use_hash = type->make_hash_key(&hash, key);
	}

	type->keep_key(ctx, key);
	fz_lock(ctx, FZ_LOCK_ALLOC);
	if (store->max != FZ_STORE_UNLIMITED)
	{
		size = store->size + itemsize;
		while (size > store->max)
		{

			if (ensure_space(ctx, size - store->max) == 0)
			{

				fz_unlock(ctx, FZ_LOCK_ALLOC);
				fz_free(ctx, item);
				type->drop_key(ctx, key);
				return NULL;
			}
		}
	}
	store->size += itemsize;

	item->key = key;
	item->val = val;
	item->size = itemsize;
	item->next = NULL;
	item->type = type;


	if (use_hash)
	{
		fz_item *existing;

		fz_try(ctx)
		{

			existing = fz_hash_insert(ctx, store->hash, &hash, item);
		}
		fz_catch(ctx)
		{
			store->size -= itemsize;
			fz_unlock(ctx, FZ_LOCK_ALLOC);
			fz_free(ctx, item);
			return NULL;
		}
		if (existing)
		{

			existing->val->refs++;
			fz_unlock(ctx, FZ_LOCK_ALLOC);
			fz_free(ctx, item);
			return existing->val;
		}
	}

	if (val->refs > 0)
		val->refs++;

	item->next = store->head;
	if (item->next)
		item->next->prev = item;
	else
		store->tail = item;
	store->head = item;
	item->prev = NULL;
	fz_unlock(ctx, FZ_LOCK_ALLOC);

	return NULL;
}
