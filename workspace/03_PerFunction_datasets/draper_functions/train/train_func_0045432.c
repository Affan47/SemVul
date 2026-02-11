bnx2x_exe_queue_free_elem(struct bnx2x *bp,
					     struct bnx2x_exeq_elem *elem)
{
	DP(BNX2X_MSG_SP, "Deleting an exe_queue element\n");
	kfree(elem);
}
