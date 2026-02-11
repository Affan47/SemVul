btrfs_init_new_buffer(struct btrfs_trans_handle *trans, struct btrfs_root *root,
		      u64 bytenr, int level)
{
	struct extent_buffer *buf;

	buf = btrfs_find_create_tree_block(root, bytenr);
	if (!buf)
		return ERR_PTR(-ENOMEM);
	btrfs_set_header_generation(buf, trans->transid);
	btrfs_set_buffer_lockdep_class(root->root_key.objectid, buf, level);
	btrfs_tree_lock(buf);
	clean_tree_block(trans, root->fs_info, buf);
	clear_bit(EXTENT_BUFFER_STALE, &buf->bflags);

	btrfs_set_lock_blocking(buf);
	btrfs_set_buffer_uptodate(buf);

	if (root->root_key.objectid == BTRFS_TREE_LOG_OBJECTID) {
		buf->log_index = root->log_transid % 2;


		if (buf->log_index == 0)
			set_extent_dirty(&root->dirty_log_pages, buf->start,
					buf->start + buf->len - 1, GFP_NOFS);
		else
			set_extent_new(&root->dirty_log_pages, buf->start,
					buf->start + buf->len - 1, GFP_NOFS);
	} else {
		buf->log_index = -1;
		set_extent_dirty(&trans->transaction->dirty_pages, buf->start,
			 buf->start + buf->len - 1, GFP_NOFS);
	}
	trans->dirty = true;

	return buf;
}
