aa_create_aafs(void)
{
	struct dentry *dent;
	int error;

	if (!apparmor_initialized)
		return 0;

	if (aa_fs_entry.dentry) {
		AA_ERROR("%s: AppArmor securityfs already exists\n", __func__);
		return -EEXIST;
	}


	error = aafs_create_dir(&aa_fs_entry, NULL);
	if (error)
		goto error;

	dent = securityfs_create_file(".load", 0666, aa_fs_entry.dentry,
				      NULL, &aa_fs_profile_load);
	if (IS_ERR(dent)) {
		error = PTR_ERR(dent);
		goto error;
	}
	ns_subload(root_ns) = dent;

	dent = securityfs_create_file(".replace", 0666, aa_fs_entry.dentry,
				      NULL, &aa_fs_profile_replace);
	if (IS_ERR(dent)) {
		error = PTR_ERR(dent);
		goto error;
	}
	ns_subreplace(root_ns) = dent;

	dent = securityfs_create_file(".remove", 0666, aa_fs_entry.dentry,
				      NULL, &aa_fs_profile_remove);
	if (IS_ERR(dent)) {
		error = PTR_ERR(dent);
		goto error;
	}
	ns_subremove(root_ns) = dent;

	mutex_lock(&root_ns->lock);
	error = __aa_fs_ns_mkdir(root_ns, aa_fs_entry.dentry, "policy", NULL);
	mutex_unlock(&root_ns->lock);

	if (error)
		goto error;

	error = aa_mk_null_file(aa_fs_entry.dentry);
	if (error)
		goto error;

	if (!aa_g_unconfined_init) {

	}


	aa_info_message("AppArmor Filesystem Enabled");
	return 0;

error:
	aa_destroy_aafs();
	AA_ERROR("Error creating AppArmor securityfs\n");
	return error;
}
