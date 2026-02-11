indexes_removefromqueue(indexes_t *indexes_p, char *fpath, queue_id_t queue_id) {


	g_hash_table_remove(indexes_p->fpath2ei_coll_ht[queue_id], fpath);

	printf_ddd("Debug3: indexes_removefromqueue(indexes_p, \"%s\", %i). It's now %i events collected in queue %i.\n", fpath, queue_id, g_hash_table_size(indexes_p->fpath2ei_coll_ht[queue_id]), queue_id);
	return 0;
}
