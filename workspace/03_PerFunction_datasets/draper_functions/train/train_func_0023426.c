afs_vlocation_fill_in_record(struct afs_vlocation *vl,
					struct key *key)
{
	struct afs_cache_vlocation vldb;
	int ret;

	_enter("");

	ASSERTCMP(vl->valid, ==, 0);

	memset(&vldb, 0, sizeof(vldb));


#ifdef CONFIG_AFS_FSCACHE
	vl->cache = fscache_acquire_cookie(vl->cell->cache,
					   &afs_vlocation_cache_index_def, vl,
					   true);
#endif

	if (vl->valid) {


		_debug("found in cache");
		ret = afs_vlocation_update_record(vl, key, &vldb);
	} else {


		ret = afs_vlocation_access_vl_by_name(vl, key, &vldb);
		if (ret < 0) {
			printk("kAFS: failed to locate '%s' in cell '%s'\n",
			       vl->vldb.name, vl->cell->name);
			return ret;
		}
	}

	afs_vlocation_apply_update(vl, &vldb);
	_leave(" = 0");
	return 0;
}
