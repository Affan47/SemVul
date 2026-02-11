mark_segment(struct shadow_tree *tree, u32 segno)
{
	int err;

	if (!btree_lookup32(&tree->segment_map, segno)) {
		err = btree_insert32(&tree->segment_map, segno, (void *)1,
				GFP_NOFS);
		BUG_ON(err);
		tree->no_shadowed_segments++;
	}
}
