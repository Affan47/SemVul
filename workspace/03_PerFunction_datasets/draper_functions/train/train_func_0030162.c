store_delete_random(struct store *store)
{
	int what;

	if (store->stock_num <= 0) return;


	what = randint0(store->stock_num);

	store_delete_index(store, what);
}
