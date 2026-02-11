resize(struct tsort_store *store, size_t new_size)
{
	if (store->alloc < new_size) {
		void **tempstore = git__realloc(store->storage, new_size * sizeof(void *));


		if (tempstore == NULL)
			return -1;

		store->storage = tempstore;
		store->alloc = new_size;
	}

	return 0;
}
