insert_free_dqentry(struct quota_handle *h, dqbuf_t buf,
				unsigned int blk)
{
	dqbuf_t tmpbuf = getdqbuf();
	struct qt_disk_dqdbheader *dh = (struct qt_disk_dqdbheader *)buf;
	struct qtree_mem_dqinfo *info = &h->qh_info.u.v2_mdqi.dqi_qtree;

	if (!tmpbuf)
		return;

	dh->dqdh_next_free = ext2fs_cpu_to_le32(info->dqi_free_entry);
	dh->dqdh_prev_free = ext2fs_cpu_to_le32(0);
	write_blk(h, blk, buf);
	if (info->dqi_free_entry) {
		read_blk(h, info->dqi_free_entry, tmpbuf);
		((struct qt_disk_dqdbheader *)tmpbuf)->dqdh_prev_free =
				ext2fs_cpu_to_le32(blk);
		write_blk(h, info->dqi_free_entry, tmpbuf);
	}
	freedqbuf(tmpbuf);
	info->dqi_free_entry = blk;
	mark_quotafile_info_dirty(h);
}
