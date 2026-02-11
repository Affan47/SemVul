container_destruct(void *_c)
{
	struct ao2_container *c = _c;
	int i;

	__ao2_callback(c, OBJ_UNLINK, cd_cb, NULL);

	for (i = 0; i < c->n_buckets; i++) {
		struct bucket_entry *current;

		while ((current = AST_LIST_REMOVE_HEAD(&c->buckets[i], entry))) {
			ast_free(current);
		}
	}

#ifdef AO2_DEBUG
	ast_atomic_fetchadd_int(&ao2.total_containers, -1);
#endif
}
