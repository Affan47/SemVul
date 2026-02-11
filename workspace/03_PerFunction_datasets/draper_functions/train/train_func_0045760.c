bnx2x_ets_get_credit_upper_bound(const u32 min_w_val)
{
	const u32 credit_upper_bound = (u32)MAXVAL((150 * min_w_val),
						MAX_PACKET_SIZE);
	return credit_upper_bound;
}
