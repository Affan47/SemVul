bnx2x_ets_e3b0_sp_pri_to_cos_init(u8 *sp_pri_to_cos)
{
	u8 pri = 0;
	for (pri = 0; pri < DCBX_MAX_NUM_COS; pri++)
		sp_pri_to_cos[pri] = DCBX_INVALID_COS;
}
