get_dcookie(struct path *path, unsigned long *cookie)
{
	int err = 0;
	struct dcookie_struct * dcs;

	mutex_lock(&dcookie_mutex);

	if (!is_live()) {
		err = -EINVAL;
		goto out;
	}

	if (path->dentry->d_flags & DCACHE_COOKIE) {
		dcs = find_dcookie((unsigned long)path->dentry);
	} else {
		dcs = alloc_dcookie(path);
		if (!dcs) {
			err = -ENOMEM;
			goto out;
		}
	}

	*cookie = dcookie_value(dcs);

out:
	mutex_unlock(&dcookie_mutex);
	return err;
}
