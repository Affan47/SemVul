cachefiles_cull(struct cachefiles_cache *cache, struct dentry *dir,
		    char *filename)
{
	struct dentry *victim;
	int ret;

	_enter(",%pd/,%s", dir, filename);

	victim = cachefiles_check_active(cache, dir, filename);
	if (IS_ERR(victim))
		return PTR_ERR(victim);

	_debug("victim -> %p %s",
	       victim, d_backing_inode(victim) ? "positive" : "negative");


	_debug("victim is cullable");

	ret = cachefiles_remove_object_xattr(cache, victim);
	if (ret < 0)
		goto error_unlock;


	_debug("bury");

	ret = cachefiles_bury_object(cache, dir, victim, false,
				     FSCACHE_OBJECT_WAS_CULLED);
	if (ret < 0)
		goto error;

	dput(victim);
	_leave(" = 0");
	return 0;

error_unlock:
	mutex_unlock(&d_inode(dir)->i_mutex);
error:
	dput(victim);
	if (ret == -ENOENT) {

		_leave(" = -ESTALE [absent]");
		return -ESTALE;
	}

	if (ret != -ENOMEM) {
		pr_err("Internal error: %d\n", ret);
		ret = -EIO;
	}

	_leave(" = %d", ret);
	return ret;
}
