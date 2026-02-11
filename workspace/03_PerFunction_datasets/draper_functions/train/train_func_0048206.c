udf_update_alloc_ext_desc(struct inode *inode,
				      struct extent_position *epos,
				      u32 lenalloc)
{
	struct super_block *sb = inode->i_sb;
	struct udf_sb_info *sbi = UDF_SB(sb);

	struct allocExtDesc *aed = (struct allocExtDesc *) (epos->bh->b_data);
	int len = sizeof(struct allocExtDesc);

	aed->lengthAllocDescs =	cpu_to_le32(lenalloc);
	if (!UDF_QUERY_FLAG(sb, UDF_FLAG_STRICT) || sbi->s_udfrev >= 0x0201)
		len += lenalloc;

	udf_update_tag(epos->bh->b_data, len);
	mark_buffer_dirty_inode(epos->bh, inode);
}
