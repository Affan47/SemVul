dir_new_leaf(struct inode *inode, const struct qstr *name)
{
	struct buffer_head *bh, *obh;
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_leaf *leaf, *oleaf;
	u32 dist = 1;
	int error;
	u32 index;
	u64 bn;

	index = name->hash >> (32 - ip->i_depth);
	error = get_first_leaf(ip, index, &obh);
	if (error)
		return error;
	do {
		dist++;
		oleaf = (struct gfs2_leaf *)obh->b_data;
		bn = be64_to_cpu(oleaf->lf_next);
		if (!bn)
			break;
		brelse(obh);
		error = get_leaf(ip, bn, &obh);
		if (error)
			return error;
	} while(1);

	gfs2_trans_add_meta(ip->i_gl, obh);

	leaf = new_leaf(inode, &bh, be16_to_cpu(oleaf->lf_depth));
	if (!leaf) {
		brelse(obh);
		return -ENOSPC;
	}
	leaf->lf_dist = cpu_to_be32(dist);
	oleaf->lf_next = cpu_to_be64(bh->b_blocknr);
	brelse(bh);
	brelse(obh);

	error = gfs2_meta_inode_buffer(ip, &bh);
	if (error)
		return error;
	gfs2_trans_add_meta(ip->i_gl, bh);
	gfs2_add_inode_blocks(&ip->i_inode, 1);
	gfs2_dinode_out(ip, bh->b_data);
	brelse(bh);
	return 0;
}
