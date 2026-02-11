bnx2x_exe_queue_alloc_elem(
	struct bnx2x *bp)
{
	DP(BNX2X_MSG_SP, "Allocating a new exe_queue element\n");
	return kzalloc(sizeof(struct bnx2x_exeq_elem), GFP_ATOMIC);
}
