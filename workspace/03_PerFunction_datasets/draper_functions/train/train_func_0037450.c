initiate_cifs_search(const unsigned int xid, struct file *file)
{
	__u16 search_flags;
	int rc = 0;
	char *full_path = NULL;
	struct cifsFileInfo *cifsFile;
	struct cifs_sb_info *cifs_sb = CIFS_FILE_SB(file);
	struct tcon_link *tlink = NULL;
	struct cifs_tcon *tcon;
	struct TCP_Server_Info *server;

	if (file->private_data == NULL) {
		tlink = cifs_sb_tlink(cifs_sb);
		if (IS_ERR(tlink))
			return PTR_ERR(tlink);

		cifsFile = kzalloc(sizeof(struct cifsFileInfo), GFP_KERNEL);
		if (cifsFile == NULL) {
			rc = -ENOMEM;
			goto error_exit;
		}
		spin_lock_init(&cifsFile->file_info_lock);
		file->private_data = cifsFile;
		cifsFile->tlink = cifs_get_tlink(tlink);
		tcon = tlink_tcon(tlink);
	} else {
		cifsFile = file->private_data;
		tcon = tlink_tcon(cifsFile->tlink);
	}

	server = tcon->ses->server;

	if (!server->ops->query_dir_first) {
		rc = -ENOSYS;
		goto error_exit;
	}

	cifsFile->invalidHandle = true;
	cifsFile->srch_inf.endOfSearch = false;

	full_path = build_path_from_dentry(file->f_path.dentry);
	if (full_path == NULL) {
		rc = -ENOMEM;
		goto error_exit;
	}

	cifs_dbg(FYI, "Full path: %s start at: %lld\n", full_path, file->f_pos);

ffirst_retry:


	if (tcon->unix_ext)
		cifsFile->srch_inf.info_level = SMB_FIND_FILE_UNIX;
	else if ((tcon->ses->capabilities &
		  tcon->ses->server->vals->cap_nt_find) == 0) {
		cifsFile->srch_inf.info_level = SMB_FIND_FILE_INFO_STANDARD;
	} else if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_SERVER_INUM) {
		cifsFile->srch_inf.info_level = SMB_FIND_FILE_ID_FULL_DIR_INFO;
	} else  {
		cifsFile->srch_inf.info_level = SMB_FIND_FILE_DIRECTORY_INFO;
	}

	search_flags = CIFS_SEARCH_CLOSE_AT_END | CIFS_SEARCH_RETURN_RESUME;
	if (backup_cred(cifs_sb))
		search_flags |= CIFS_SEARCH_BACKUP_SEARCH;

	rc = server->ops->query_dir_first(xid, tcon, full_path, cifs_sb,
					  &cifsFile->fid, search_flags,
					  &cifsFile->srch_inf);

	if (rc == 0)
		cifsFile->invalidHandle = false;


	else if ((rc == -EOPNOTSUPP) &&
		(cifs_sb->mnt_cifs_flags & CIFS_MOUNT_SERVER_INUM)) {
		cifs_sb->mnt_cifs_flags &= ~CIFS_MOUNT_SERVER_INUM;
		goto ffirst_retry;
	}
error_exit:
	kfree(full_path);
	cifs_put_tlink(tlink);
	return rc;
}
