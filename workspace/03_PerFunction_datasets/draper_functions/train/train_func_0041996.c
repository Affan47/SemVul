inode_new_generation_wait_start(struct inode *inode, struct peer *peer)
{
	struct inode_open_state *ios = inode->u.c.state;
	static const char diag[] = "inode_new_generation_wait_start";

	if (ios == NULL) {
		gflog_error(GFARM_MSG_1002248, "%s: not opened", diag);
		return (GFARM_ERR_BAD_FILE_DESCRIPTOR);
	}
	ios->u.f.event_source = peer;
	return (GFARM_ERR_NO_ERROR);
}
