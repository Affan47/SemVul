bnx2x_vf_by_abs_fid(struct bnx2x *bp, u16 abs_vfid)
{
	u16 idx =  (u16)bnx2x_vf_idx_by_abs_fid(bp, abs_vfid);
	return (idx < BNX2X_NR_VIRTFN(bp)) ? BP_VF(bp, idx) : NULL;
}
