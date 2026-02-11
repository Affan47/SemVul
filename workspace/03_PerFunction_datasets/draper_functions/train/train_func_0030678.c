f2fs_lookup_extent_tree(struct inode *inode, pgoff_t pgofs,
							struct extent_info *ei)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	struct extent_tree *et = F2FS_I(inode)->extent_tree;
	struct extent_node *en;
	bool ret = false;

	f2fs_bug_on(sbi, !et);

	trace_f2fs_lookup_extent_tree_start(inode, pgofs);

	read_lock(&et->lock);

	if (et->largest.fofs <= pgofs &&
			et->largest.fofs + et->largest.len > pgofs) {
		*ei = et->largest;
		ret = true;
		stat_inc_largest_node_hit(sbi);
		goto out;
	}

	en = __lookup_extent_tree(sbi, et, pgofs);
	if (en) {
		*ei = en->ei;
		spin_lock(&sbi->extent_lock);
		if (!list_empty(&en->list))
			list_move_tail(&en->list, &sbi->extent_list);
		et->cached_en = en;
		spin_unlock(&sbi->extent_lock);
		ret = true;
	}
out:
	stat_inc_total_hit(sbi);
	read_unlock(&et->lock);

	trace_f2fs_lookup_extent_tree_end(inode, pgofs, ei);
	return ret;
}
