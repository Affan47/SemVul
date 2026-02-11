audit_dupe_exe(struct audit_krule *new, struct audit_krule *old)
{
	struct audit_fsnotify_mark *audit_mark;
	char *pathname;

	pathname = kstrdup(audit_mark_path(old->exe), GFP_KERNEL);
	if (!pathname)
		return -ENOMEM;

	audit_mark = audit_alloc_mark(new, pathname, strlen(pathname));
	if (IS_ERR(audit_mark)) {
		kfree(pathname);
		return PTR_ERR(audit_mark);
	}
	new->exe = audit_mark;

	return 0;
}
