pick_and_place_monster(struct cave *c, int y, int x, int depth, bool slp,
	bool grp, byte origin)
{
	int r_idx;


	r_idx = get_mon_num(depth);


	if (!r_idx) return (FALSE);


	return (place_new_monster(c, y, x, r_idx, slp, grp, origin));
}
