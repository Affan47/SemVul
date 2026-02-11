ntfs_rl_vcn_to_lcn(const runlist_element *rl, const VCN vcn)
{
	int i;

	BUG_ON(vcn < 0);


	if (unlikely(!rl))
		return LCN_RL_NOT_MAPPED;


	if (unlikely(vcn < rl[0].vcn))
		return LCN_ENOENT;

	for (i = 0; likely(rl[i].length); i++) {
		if (unlikely(vcn < rl[i+1].vcn)) {
			if (likely(rl[i].lcn >= (LCN)0))
				return rl[i].lcn + (vcn - rl[i].vcn);
			return rl[i].lcn;
		}
	}


	if (likely(rl[i].lcn < (LCN)0))
		return rl[i].lcn;

	return LCN_ENOENT;
}
