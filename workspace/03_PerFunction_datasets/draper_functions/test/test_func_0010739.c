exp_parent(struct cache_detail *cd, struct auth_domain *clp, struct path *path)
{
	struct dentry *saved = dget(path->dentry);
	struct svc_export *exp = exp_get_by_name(cd, clp, path, NULL);

	while (PTR_ERR(exp) == -ENOENT && !IS_ROOT(path->dentry)) {
		struct dentry *parent = dget_parent(path->dentry);
		dput(path->dentry);
		path->dentry = parent;
		exp = exp_get_by_name(cd, clp, path, NULL);
	}
	dput(path->dentry);
	path->dentry = saved;
	return exp;
}
