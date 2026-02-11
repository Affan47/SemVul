kill_alias(void *_block, unsigned long ignore0,
		u64 ignore1, u64 ignore2, size_t ignore3)
{
	struct logfs_block *block = _block;
	struct super_block *sb = block->sb;
	struct logfs_super *super = logfs_super(sb);
	struct object_alias_item *item;

	while (!list_empty(&block->item_list)) {
		item = list_entry(block->item_list.next, typeof(*item), list);
		list_del(&item->list);
		mempool_free(item, super->s_alias_pool);
	}
	block->ops->free_block(sb, block);
}
