cifs_do_mount(struct file_system_type *fs_type,
	      int flags, const char *dev_name, void *data)
{
	int rc;
	struct super_block *sb;
	struct cifs_sb_info *cifs_sb;
	struct smb_vol *volume_info;
	struct cifs_mnt_data mnt_data;
	struct dentry *root;

	cifs_dbg(FYI, "Devname: %s flags: %d\n", dev_name, flags);

	volume_info = cifs_get_volume_info((char *)data, dev_name);
	if (IS_ERR(volume_info))
		return ERR_CAST(volume_info);

	cifs_sb = kzalloc(sizeof(struct cifs_sb_info), GFP_KERNEL);
	if (cifs_sb == NULL) {
		root = ERR_PTR(-ENOMEM);
		goto out_nls;
	}

	cifs_sb->mountdata = kstrndup(data, PAGE_SIZE, GFP_KERNEL);
	if (cifs_sb->mountdata == NULL) {
		root = ERR_PTR(-ENOMEM);
		goto out_free;
	}

	rc = cifs_setup_cifs_sb(volume_info, cifs_sb);
	if (rc) {
		root = ERR_PTR(rc);
		goto out_free;
	}

	rc = cifs_mount(cifs_sb, volume_info);
	if (rc) {
		if (!(flags & MS_SILENT))
			cifs_dbg(VFS, "cifs_mount failed w/return code = %d\n",
				 rc);
		root = ERR_PTR(rc);
		goto out_free;
	}

	mnt_data.vol = volume_info;
	mnt_data.cifs_sb = cifs_sb;
	mnt_data.flags = flags;


	flags |= MS_NODIRATIME | MS_NOATIME;

	sb = sget(fs_type, cifs_match_super, cifs_set_super, flags, &mnt_data);
	if (IS_ERR(sb)) {
		root = ERR_CAST(sb);
		cifs_umount(cifs_sb);
		goto out;
	}

	if (sb->s_root) {
		cifs_dbg(FYI, "Use existing superblock\n");
		cifs_umount(cifs_sb);
	} else {
		rc = cifs_read_super(sb);
		if (rc) {
			root = ERR_PTR(rc);
			goto out_super;
		}

		sb->s_flags |= MS_ACTIVE;
	}

	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_USE_PREFIX_PATH)
		root = dget(sb->s_root);
	else
		root = cifs_get_root(volume_info, sb);

	if (IS_ERR(root))
		goto out_super;

	cifs_dbg(FYI, "dentry root is: %p\n", root);
	goto out;

out_super:
	deactivate_locked_super(sb);
out:
	cifs_cleanup_volume_info(volume_info);
	return root;

out_free:
	kfree(cifs_sb->prepath);
	kfree(cifs_sb->mountdata);
	kfree(cifs_sb);
out_nls:
	unload_nls(volume_info->local_nls);
	goto out;
}
