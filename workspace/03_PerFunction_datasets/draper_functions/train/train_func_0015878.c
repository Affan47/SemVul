audit_to_watch(struct audit_krule *krule, char *path, int len, u32 op)
{
	struct audit_watch *watch;

	if (!audit_watch_group)
		return -EOPNOTSUPP;

	if (path[0] != '/' || path[len-1] == '/' ||
	    krule->listnr != AUDIT_FILTER_EXIT ||
	    op != Audit_equal ||
	    krule->inode_f || krule->watch || krule->tree)
		return -EINVAL;

	watch = audit_init_watch(path);
	if (IS_ERR(watch))
		return PTR_ERR(watch);

	krule->watch = watch;

	return 0;
}
