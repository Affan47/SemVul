ocfs2_seek_data_hole_offset(struct file *file, loff_t *offset, int whence)
{
	struct inode *inode = file->f_mapping->host;
	int ret;
	unsigned int is_last = 0, is_data = 0;
	u16 cs_bits = OCFS2_SB(inode->i_sb)->s_clustersize_bits;
	u32 cpos, cend, clen, hole_size;
	u64 extoff, extlen;
	struct buffer_head *di_bh = NULL;
	struct ocfs2_extent_rec rec;

	BUG_ON(whence != SEEK_DATA && whence != SEEK_HOLE);

	ret = ocfs2_inode_lock(inode, &di_bh, 0);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	down_read(&OCFS2_I(inode)->ip_alloc_sem);

	if (*offset >= i_size_read(inode)) {
		ret = -ENXIO;
		goto out_unlock;
	}

	if (OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL) {
		if (whence == SEEK_HOLE)
			*offset = i_size_read(inode);
		goto out_unlock;
	}

	clen = 0;
	cpos = *offset >> cs_bits;
	cend = ocfs2_clusters_for_bytes(inode->i_sb, i_size_read(inode));

	while (cpos < cend && !is_last) {
		ret = ocfs2_get_clusters_nocache(inode, di_bh, cpos, &hole_size,
						 &rec, &is_last);
		if (ret) {
			mlog_errno(ret);
			goto out_unlock;
		}

		extoff = cpos;
		extoff <<= cs_bits;

		if (rec.e_blkno == 0ULL) {
			clen = hole_size;
			is_data = 0;
		} else {
			clen = le16_to_cpu(rec.e_leaf_clusters) -
				(cpos - le32_to_cpu(rec.e_cpos));
			is_data = (rec.e_flags & OCFS2_EXT_UNWRITTEN) ?  0 : 1;
		}

		if ((!is_data && whence == SEEK_HOLE) ||
		    (is_data && whence == SEEK_DATA)) {
			if (extoff > *offset)
				*offset = extoff;
			goto out_unlock;
		}

		if (!is_last)
			cpos += clen;
	}

	if (whence == SEEK_HOLE) {
		extoff = cpos;
		extoff <<= cs_bits;
		extlen = clen;
		extlen <<=  cs_bits;

		if ((extoff + extlen) > i_size_read(inode))
			extlen = i_size_read(inode) - extoff;
		extoff += extlen;
		if (extoff > *offset)
			*offset = extoff;
		goto out_unlock;
	}

	ret = -ENXIO;

out_unlock:

	brelse(di_bh);

	up_read(&OCFS2_I(inode)->ip_alloc_sem);

	ocfs2_inode_unlock(inode, 0);
out:
	return ret;
}
