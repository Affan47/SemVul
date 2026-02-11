vxfs_get_ilist(struct vxfs_oltilist *ilistp, struct vxfs_sb_info *infp)
{
	BUG_ON(infp->vsi_iext);
	infp->vsi_iext = ilistp->olt_iext[0];
}
