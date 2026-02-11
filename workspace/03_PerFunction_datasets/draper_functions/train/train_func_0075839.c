hdfs_copy_fileinfo(pfs_name *name, hdfsFileInfo *file_info, struct pfs_stat *buf) {
		int file_uid;
		int file_gid;

		pfs_service_emulate_stat(name, buf);

		if (file_info->mKind == kObjectKindDirectory) {
			buf->st_mode  = S_IFDIR;
		} else {
			buf->st_mode = S_IFREG;
		}

		buf->st_mode   |= file_info->mPermissions;
		buf->st_size    = file_info->mSize;
		buf->st_mtime   = file_info->mLastMod;
		buf->st_atime   = file_info->mLastAccess;
		buf->st_blksize = file_info->mBlockSize;

		file_uid = get_uid_from_name(file_info->mOwner);
		if (file_uid >= 0) {
			buf->st_uid = file_uid;
		}

		file_gid = get_gid_from_name(file_info->mGroup);
		if (file_gid >= 0) {
			buf->st_gid = file_gid;
		}
	}
