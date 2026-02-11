fill_shadow_tree(struct inode *inode, struct page *page,
		struct logfs_shadow *shadow)
{
	struct logfs_super *super = logfs_super(inode->i_sb);
	struct logfs_block *block = logfs_block(page);
	struct shadow_tree *tree = &super->s_shadow_tree;

	if (PagePrivate(page)) {
		if (block->alias_map)
			super->s_no_object_aliases -= bitmap_weight(
					block->alias_map, LOGFS_BLOCK_FACTOR);
		logfs_handle_transaction(inode, block->ta);
		block->ops->free_block(inode->i_sb, block);
	}
	if (shadow) {
		if (shadow->old_ofs)
			btree_insert64(&tree->old, shadow->old_ofs, shadow,
					GFP_NOFS);
		else
			btree_insert64(&tree->new, shadow->new_ofs, shadow,
					GFP_NOFS);

		super->s_dirty_used_bytes += shadow->new_len;
		super->s_dirty_free_bytes += shadow->old_len;
		mark_segment(tree, shadow->old_ofs >> super->s_segshift);
		mark_segment(tree, shadow->new_ofs >> super->s_segshift);
	}
}
