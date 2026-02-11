gfs2_xattr_acl_chmod(struct gfs2_inode *ip, struct iattr *attr, char *data)
{
	struct inode *inode = &ip->i_inode;
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct gfs2_ea_location el;
	int error;

	error = gfs2_ea_find(ip, GFS2_EATYPE_SYS, GFS2_POSIX_ACL_ACCESS, &el);
	if (error)
		return error;

	if (GFS2_EA_IS_STUFFED(el.el_ea)) {
		error = gfs2_trans_begin(sdp, RES_DINODE + RES_EATTR, 0);
		if (error == 0) {
			gfs2_trans_add_meta(ip->i_gl, el.el_bh);
			memcpy(GFS2_EA2DATA(el.el_ea), data,
			       GFS2_EA_DATA_LEN(el.el_ea));
		}
	} else {
		error = ea_acl_chmod_unstuffed(ip, el.el_ea, data);
	}

	brelse(el.el_bh);
	if (error)
		return error;

	error = gfs2_setattr_simple(inode, attr);
	gfs2_trans_end(sdp);
	return error;
}
