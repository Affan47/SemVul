inode_replicated(struct file_replicating *fr,
	gfarm_int32_t src_errcode, gfarm_int32_t dst_errcode, gfarm_off_t size)
{
	struct inode *inode = fr->inode;
	int transaction = 0;
	gfarm_error_t e = GFARM_ERR_NO_ERROR;
	struct dead_file_copy *dfc;
	static const char diag[] = "inode_replicated";

	if (db_begin(diag) == GFARM_ERR_NO_ERROR)
		transaction = 1;

	if (src_errcode == GFARM_ERR_NO_ERROR &&
	    dst_errcode == GFARM_ERR_NO_ERROR &&
	    size == inode_get_size(inode) &&
	    fr->igen == inode_get_gen(inode)) {
		e = inode_add_replica(inode, fr->dst, 1);
	} else {
		if (src_errcode != GFARM_ERR_NO_ERROR ||
		    dst_errcode != GFARM_ERR_NO_ERROR)
			gflog_error(GFARM_MSG_1002257,
			    "error at %lld:%lld replication to %s: "
			    "src=%d dst=%d",
			    (long long)inode_get_number(inode),
			    (long long)fr->igen,
			    host_name(fr->dst), src_errcode, dst_errcode);
		if (debug_mode && (size != inode_get_size(inode) ||
		    fr->igen != inode_get_gen(inode)))
			gflog_debug(GFARM_MSG_1001763,
			    "invalid replica: "
			    "(gen:%lld, size:%lld) "
			    "should be (gen:%lld, size:%lld)",
			    (long long)fr->igen, (long long)size,
			    (long long)inode_get_gen(inode),
			    (long long)inode_get_size(inode));
		e = inode_remove_replica_gen_deferred(inode, fr->dst, fr->igen,
		    0, 1, 0, &dfc);
		if (e == GFARM_ERR_NO_ERROR) {
			removal_pendingq_enqueue(dfc);
		} else if (e == GFARM_ERR_NO_SUCH_OBJECT) {
			gflog_info(GFARM_MSG_1002433,
			    "cannot remove an incomplete replica "
			    "(%s, %lld:%lld): probably already removed",
			    host_name(fr->dst),
			    (long long)inode_get_number(inode),
			    (long long)fr->igen);
		} else {
			gflog_error(GFARM_MSG_1002434,
			    "cannot remove an incomplete replica "
			    "(%s, %lld:%lld): %s",
			    host_name(fr->dst),
			    (long long)inode_get_number(inode),
			    (long long)fr->igen,
			    gfarm_error_string(e));
		}
		e = GFARM_ERR_INVALID_FILE_REPLICA;
	}

	if (fr->cleanup != NULL) {


		if (src_errcode == GFARM_ERR_NO_ERROR &&
		    dead_file_copy_is_removable(fr->cleanup))
			removal_pendingq_enqueue(fr->cleanup);
		else
			dead_file_copy_mark_deferred(fr->cleanup);
	} else if (e == GFARM_ERR_NO_ERROR) {

		dead_file_copy_replica_status_changed(inode_get_number(inode),
		    fr->dst);
	}

	file_replicating_free(fr);

	if (transaction)
		db_end(diag);
	return (e);
}
