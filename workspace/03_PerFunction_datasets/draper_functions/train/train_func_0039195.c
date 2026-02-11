free_stores(void)
{
	struct owner *o;
	struct owner *next;
	int i;


	for (i = 0; i < MAX_STORES; i++)
	{

		struct store *store = &stores[i];


		mem_free(store->stock);
		mem_free(store->table);

		for (o = store->owners; o; o = next) {
			next = o->next;
			string_free(o->name);
			mem_free(o);
		}
	}
	mem_free(stores);
}
