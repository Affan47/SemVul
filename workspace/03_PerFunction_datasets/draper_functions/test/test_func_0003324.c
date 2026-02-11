udf_discard_prealloc(struct inode *inode)
{
	struct extent_position epos = { NULL, 0, {0, 0} };
	struct kernel_lb_addr eloc;
	uint32_t elen;
	uint64_t lbcount = 0;
	int8_t etype = -1, netype;
	int adsize;
	struct udf_inode_info *iinfo = UDF_I(inode);

	if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB ||
	    inode->i_size == iinfo->i_lenExtents)
		return;

	if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
		adsize = sizeof(struct short_ad);
	else if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
		adsize = sizeof(struct long_ad);
	else
		adsize = 0;

	epos.block = iinfo->i_location;


	while ((netype = udf_next_aext(inode, &epos, &eloc, &elen, 1)) != -1) {
		etype = netype;
		lbcount += elen;
	}
	if (etype == (EXT_NOT_RECORDED_ALLOCATED >> 30)) {
		epos.offset -= adsize;
		lbcount -= elen;
		extent_trunc(inode, &epos, &eloc, etype, elen, 0);
		if (!epos.bh) {
			iinfo->i_lenAlloc =
				epos.offset -
				udf_file_entry_alloc_offset(inode);
			mark_inode_dirty(inode);
		} else {
			struct allocExtDesc *aed =
				(struct allocExtDesc *)(epos.bh->b_data);
			aed->lengthAllocDescs =
				cpu_to_le32(epos.offset -
					    sizeof(struct allocExtDesc));
			if (!UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_STRICT) ||
			    UDF_SB(inode->i_sb)->s_udfrev >= 0x0201)
				udf_update_tag(epos.bh->b_data, epos.offset);
			else
				udf_update_tag(epos.bh->b_data,
					       sizeof(struct allocExtDesc));
			mark_buffer_dirty_inode(epos.bh, inode);
		}
	}


	iinfo->i_lenExtents = lbcount;
	brelse(epos.bh);
}
