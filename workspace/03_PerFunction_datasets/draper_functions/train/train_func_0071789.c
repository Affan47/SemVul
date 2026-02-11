quota_data_sub(quota_ctx_t qctx, struct ext2_inode *inode, ext2_ino_t ino,
		    qsize_t space)
{
	struct dquot	*dq;
	dict_t		*dict;
	int		i;

	if (!qctx)
		return;

	log_debug("SUB_DATA: Inode: %u, UID/GID: %u/%u, space: %ld", ino,
			inode_uid(*inode),
			inode_gid(*inode), space);
	for (i = 0; i < MAXQUOTAS; i++) {
		dict = qctx->quota_dict[i];
		if (dict) {
			dq = get_dq(dict, get_qid(inode, i));
			dq->dq_dqb.dqb_curspace -= space;
		}
	}
}
