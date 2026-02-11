db_free_unlock(struct dbt *table)
{
	if(--table->free_lock == 0) {
		int i;
		for(i = 0; i < table->free_count ; i++) {
			db_rebalance_erase(table->free_list[i].z,table->free_list[i].root);
			if(table->cmp == strdb_cmp) {
				aFree(table->free_list[i].z->key);
			}
			free_dbn(table->free_list[i].z);
			table->item_count--;
		}
		table->free_count = 0;
	}
}
