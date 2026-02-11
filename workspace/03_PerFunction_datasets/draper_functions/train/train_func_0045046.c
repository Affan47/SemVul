get_a_matching_object(struct proc_acl *subject,
				const char *filename, const char *origname, int follow)
{
	struct file_acl *tmpf, *tmpg;
	struct proc_acl *tmpp = subject;
	do {
		tmpf = lookup_acl_object_by_name(tmpp, filename);
		if (!tmpf) {
			if (follow)
				tmpf = lookup_acl_object_by_inodev(tmpp, filename);
			else
				tmpf = lookup_acl_object_by_inodev_nofollow(tmpp, filename);
		}
		if (tmpf) {

			for_each_globbed(tmpg, tmpf) {
				if (!fnmatch(tmpg->filename, origname, 0))
					return tmpg;
			}
			return tmpf;
		}
	} while ((tmpp = tmpp->parent_subject));

	return NULL;
}
