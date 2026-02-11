name_cache_delete(struct send_ctx *sctx,
			      struct name_cache_entry *nce)
{
	struct list_head *nce_head;

	nce_head = radix_tree_lookup(&sctx->name_cache,
			(unsigned long)nce->ino);
	if (!nce_head) {
		btrfs_err(sctx->send_root->fs_info,
	      "name_cache_delete lookup failed ino %llu cache size %d, leaking memory",
			nce->ino, sctx->name_cache_size);
	}

	list_del(&nce->radix_list);
	list_del(&nce->list);
	sctx->name_cache_size--;


	if (nce_head && list_empty(nce_head)) {
		radix_tree_delete(&sctx->name_cache, (unsigned long)nce->ino);
		kfree(nce_head);
	}
}
