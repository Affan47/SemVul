cifs_filldir(char *find_entry, struct file *file,
		struct dir_context *ctx,
		char *scratch_buf, unsigned int max_len)
{
	struct cifsFileInfo *file_info = file->private_data;
	struct super_block *sb = file_inode(file)->i_sb;
	struct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	struct cifs_dirent de = { NULL, };
	struct cifs_fattr fattr;
	struct qstr name;
	int rc = 0;
	ino_t ino;

	rc = cifs_fill_dirent(&de, find_entry, file_info->srch_inf.info_level,
			      file_info->srch_inf.unicode);
	if (rc)
		return rc;

	if (de.namelen > max_len) {
		cifs_dbg(VFS, "bad search response length %zd past smb end\n",
			 de.namelen);
		return -EINVAL;
	}


	if (cifs_entry_is_dot(&de, file_info->srch_inf.unicode))
		return 0;

	if (file_info->srch_inf.unicode) {
		struct nls_table *nlt = cifs_sb->local_nls;
		int map_type;

		map_type = cifs_remap(cifs_sb);
		name.name = scratch_buf;
		name.len =
			cifs_from_utf16((char *)name.name, (__le16 *)de.name,
					UNICODE_NAME_MAX,
					min_t(size_t, de.namelen,
					      (size_t)max_len), nlt, map_type);
		name.len -= nls_nullsize(nlt);
	} else {
		name.name = de.name;
		name.len = de.namelen;
	}

	switch (file_info->srch_inf.info_level) {
	case SMB_FIND_FILE_UNIX:
		cifs_unix_basic_to_fattr(&fattr,
					 &((FILE_UNIX_INFO *)find_entry)->basic,
					 cifs_sb);
		break;
	case SMB_FIND_FILE_INFO_STANDARD:
		cifs_std_info_to_fattr(&fattr,
				       (FIND_FILE_STANDARD_INFO *)find_entry,
				       cifs_sb);
		break;
	default:
		cifs_dir_info_to_fattr(&fattr,
				       (FILE_DIRECTORY_INFO *)find_entry,
				       cifs_sb);
		break;
	}

	if (de.ino && (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_SERVER_INUM)) {
		fattr.cf_uniqueid = de.ino;
	} else {
		fattr.cf_uniqueid = iunique(sb, ROOT_I);
		cifs_autodisable_serverino(cifs_sb);
	}

	if ((cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MF_SYMLINKS) &&
	    couldbe_mf_symlink(&fattr))


		fattr.cf_flags |= CIFS_FATTR_NEED_REVAL;

	cifs_prime_dcache(file->f_path.dentry, &name, &fattr);

	ino = cifs_uniqueid_to_ino_t(fattr.cf_uniqueid);
	return !dir_emit(ctx, name.name, name.len, ino, fattr.cf_dtype);
}
