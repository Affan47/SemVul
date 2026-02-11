valid_rs(struct raid_set *rs)
{
	return (S_OK(rs->status) || S_INCONSISTENT(rs->status)||
		S_NOSYNC(rs->status)) && !T_SPARE(rs);
}
