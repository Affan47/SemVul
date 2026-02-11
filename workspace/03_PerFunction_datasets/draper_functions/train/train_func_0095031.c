acct_get(struct pid_namespace *ns)
{
	struct bsd_acct_struct *res;
again:
	smp_rmb();
	rcu_read_lock();
	res = to_acct(ACCESS_ONCE(ns->bacct));
	if (!res) {
		rcu_read_unlock();
		return NULL;
	}
	if (!atomic_long_inc_not_zero(&res->count)) {
		rcu_read_unlock();
		cpu_relax();
		goto again;
	}
	rcu_read_unlock();
	mutex_lock(&res->lock);
	if (res != to_acct(ACCESS_ONCE(ns->bacct))) {
		mutex_unlock(&res->lock);
		acct_put(res);
		goto again;
	}
	return res;
}
