nilfs_sufile_do_free(struct inode *sufile, __u64 segnum,
			  struct buffer_head *header_bh,
			  struct buffer_head *su_bh)
{
	struct nilfs_segment_usage *su;
	void *kaddr;
	int sudirty;

	kaddr = kmap_atomic(su_bh->b_page);
	su = nilfs_sufile_block_get_segment_usage(sufile, segnum, su_bh, kaddr);
	if (nilfs_segment_usage_clean(su)) {
		printk(KERN_WARNING "%s: segment %llu is already clean\n",
		       __func__, (unsigned long long)segnum);
		kunmap_atomic(kaddr);
		return;
	}
	WARN_ON(nilfs_segment_usage_error(su));
	WARN_ON(!nilfs_segment_usage_dirty(su));

	sudirty = nilfs_segment_usage_dirty(su);
	nilfs_segment_usage_set_clean(su);
	kunmap_atomic(kaddr);
	mark_buffer_dirty(su_bh);

	nilfs_sufile_mod_counter(header_bh, 1, sudirty ? (u64)-1 : 0);
	NILFS_SUI(sufile)->ncleansegs++;

	nilfs_mdt_mark_dirty(sufile);

	trace_nilfs2_segment_usage_freed(sufile, segnum);
}
