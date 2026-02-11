ftrace_set_hash(struct ftrace_ops *ops, unsigned char *buf, int len,
		unsigned long ip, int remove, int reset, int enable)
{
	struct ftrace_hash **orig_hash;
	struct ftrace_ops_hash old_hash_ops;
	struct ftrace_hash *old_hash;
	struct ftrace_hash *hash;
	int ret;

	if (unlikely(ftrace_disabled))
		return -ENODEV;

	mutex_lock(&ops->func_hash->regex_lock);

	if (enable)
		orig_hash = &ops->func_hash->filter_hash;
	else
		orig_hash = &ops->func_hash->notrace_hash;

	if (reset)
		hash = alloc_ftrace_hash(FTRACE_HASH_DEFAULT_BITS);
	else
		hash = alloc_and_copy_ftrace_hash(FTRACE_HASH_DEFAULT_BITS, *orig_hash);

	if (!hash) {
		ret = -ENOMEM;
		goto out_regex_unlock;
	}

	if (buf && !ftrace_match_records(hash, buf, len)) {
		ret = -EINVAL;
		goto out_regex_unlock;
	}
	if (ip) {
		ret = ftrace_match_addr(hash, ip, remove);
		if (ret < 0)
			goto out_regex_unlock;
	}

	mutex_lock(&ftrace_lock);
	old_hash = *orig_hash;
	old_hash_ops.filter_hash = ops->func_hash->filter_hash;
	old_hash_ops.notrace_hash = ops->func_hash->notrace_hash;
	ret = ftrace_hash_move(ops, enable, orig_hash, hash);
	if (!ret) {
		ftrace_ops_update_code(ops, &old_hash_ops);
		free_ftrace_hash_rcu(old_hash);
	}
	mutex_unlock(&ftrace_lock);

 out_regex_unlock:
	mutex_unlock(&ops->func_hash->regex_lock);

	free_ftrace_hash(hash);
	return ret;
}
