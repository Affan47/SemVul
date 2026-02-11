bnx2x_ets_e3b0_set_credit_upper_bound_pbf(
	const struct link_params *params,
	const u32 min_w_val)
{
	struct bnx2x *bp = params->bp;
	const u32 credit_upper_bound =
	    bnx2x_ets_get_credit_upper_bound(min_w_val);
	const u8 port = params->port;
	u32 base_upper_bound = 0;
	u8 max_cos = 0;
	u8 i = 0;


	if (!port) {
		base_upper_bound = PBF_REG_COS0_UPPER_BOUND_P0;
		max_cos = DCBX_E3B0_MAX_NUM_COS_PORT0;
	} else {
		base_upper_bound = PBF_REG_COS0_UPPER_BOUND_P1;
		max_cos = DCBX_E3B0_MAX_NUM_COS_PORT1;
	}

	for (i = 0; i < max_cos; i++)
		REG_WR(bp, base_upper_bound + (i << 2), credit_upper_bound);
}
