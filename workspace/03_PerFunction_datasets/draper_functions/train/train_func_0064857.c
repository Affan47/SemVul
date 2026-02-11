rb_clear_bmap(ext2fs_generic_bitmap bitmap)
{
	struct ext2fs_rb_private *bp;

	bp = (struct ext2fs_rb_private *) bitmap->private;

	rb_free_tree(&bp->root);
	bp->rcursor = NULL;
	bp->rcursor_next = NULL;
	bp->wcursor = NULL;
	check_tree(&bp->root, __func__);
}
