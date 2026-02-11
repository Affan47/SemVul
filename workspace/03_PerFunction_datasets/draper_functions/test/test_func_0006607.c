bnx2x_mcast_validate_e1h(struct bnx2x *bp,
				    struct bnx2x_mcast_ramrod_params *p,
				    enum bnx2x_mcast_cmd cmd)
{

	if ((cmd == BNX2X_MCAST_CMD_DEL) || (cmd == BNX2X_MCAST_CMD_RESTORE))
		p->mcast_list_len = 1;

	return 0;
}
