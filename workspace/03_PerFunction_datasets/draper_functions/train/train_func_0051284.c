bnx2x_mcast_clear_first_bin(struct bnx2x_mcast_obj *o)
{
	int cur_bit = bnx2x_mcast_get_next_bin(o, 0);

	if (cur_bit >= 0)
		BIT_VEC64_CLEAR_BIT(o->registry.aprox_match.vec, cur_bit);

	return cur_bit;
}
