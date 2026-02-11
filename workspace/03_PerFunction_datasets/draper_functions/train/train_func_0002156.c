get_set_type(struct lib_context *lc, void *v)
{
	struct raid_set *rs = v;


	return is_stacked(rs) ? get_stacked_type(rs) : get_type(lc, rs->type);
}
