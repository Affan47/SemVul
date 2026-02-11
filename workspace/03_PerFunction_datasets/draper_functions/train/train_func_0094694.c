au_sysrq_fin(void)
{
	int err;

	err = unregister_sysrq_key(*aufs_sysrq_key, &au_sysrq_op);
	if (unlikely(err))
		pr_err("err %d (ignored)\n", err);
}
