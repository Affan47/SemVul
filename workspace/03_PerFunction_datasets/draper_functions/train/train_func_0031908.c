ostore_erase_segment(struct logfs_area *area)
{
	struct super_block *sb = area->a_sb;
	struct logfs_segment_header sh;
	u64 ofs;
	int err;

	err = logfs_erase_segment(sb, area->a_segno, 0);
	if (err)
		return err;

	sh.pad = 0;
	sh.type = SEG_OSTORE;
	sh.level = (__force u8)area->a_level;
	sh.segno = cpu_to_be32(area->a_segno);
	sh.ec = cpu_to_be32(area->a_erase_count);
	sh.gec = cpu_to_be64(logfs_super(sb)->s_gec);
	sh.crc = logfs_crc32(&sh, sizeof(sh), 4);

	logfs_set_segment_erased(sb, area->a_segno, area->a_erase_count,
			area->a_level);

	ofs = dev_ofs(sb, area->a_segno, 0);
	area->a_used_bytes = sizeof(sh);
	logfs_buf_write(area, ofs, &sh, sizeof(sh));
	return 0;
}
