fuse_reply_lock(fuse_req_t req, const struct flock *lock)
{
	struct fuse_lk_out arg;

	memset(&arg, 0, sizeof(arg));
	arg.lk.type = lock->l_type;
	if (lock->l_type != F_UNLCK) {
		arg.lk.start = lock->l_start;
		if (lock->l_len == 0)
			arg.lk.end = OFFSET_MAX;
		else
			arg.lk.end = lock->l_start + lock->l_len - 1;
	}
	arg.lk.pid = lock->l_pid;
	return send_reply_ok(req, &arg, sizeof(arg));
}
