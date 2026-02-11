logfs_open_area(struct logfs_area *area, size_t bytes)
{
	struct super_block *sb = area->a_sb;
	struct logfs_super *super = logfs_super(sb);
	int err, closed = 0;

	if (area->a_is_open && area->a_used_bytes + bytes <= super->s_segsize)
		return 0;

	if (area->a_is_open) {
		u64 ofs = dev_ofs(sb, area->a_segno, area->a_written_bytes);
		u32 len = super->s_segsize - area->a_written_bytes;

		log_gc("logfs_close_area(%x)\n", area->a_segno);
		pad_wbuf(area, 1);
		super->s_devops->writeseg(area->a_sb, ofs, len);
		freeseg(sb, area->a_segno);
		closed = 1;
	}

	area->a_used_bytes = 0;
	area->a_written_bytes = 0;
again:
	area->a_ops->get_free_segment(area);
	area->a_ops->get_erase_count(area);

	log_gc("logfs_open_area(%x, %x)\n", area->a_segno, area->a_level);
	err = area->a_ops->erase_segment(area);
	if (err) {
		printk(KERN_WARNING "LogFS: Error erasing segment %x\n",
				area->a_segno);
		logfs_mark_segment_bad(sb, area->a_segno);
		goto again;
	}
	area->a_is_open = 1;
	return closed;
}
