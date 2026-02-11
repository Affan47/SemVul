inode_rename(
	struct inode *sdir, char *sname,
	struct inode *ddir, char *dname,
	struct process *process)
{
	gfarm_error_t e;
	struct user *user = process_get_user(process);
	struct inode *src, *dst;

	if (user == NULL) {
		gflog_debug(GFARM_MSG_1001742, "process_get_user() failed");
		return (GFARM_ERR_OPERATION_NOT_PERMITTED);
	}


	if ((e = inode_access(sdir, user, GFS_X_OK|GFS_W_OK)) !=
	    GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1001743,
			"inode_access() failed: %s",
			gfarm_error_string(e));
		return (e);
	}
	if ((e = inode_lookup_by_name(sdir, sname, process, 0, &src))
	    != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1001744,
			"inode_lookup_by_name() failed: %s",
			gfarm_error_string(e));
		return (e);
	}
	if (strchr(sname, '/') != NULL) {
		gflog_debug(GFARM_MSG_1001745,
			"argument 'sname' is invalid");
		return (GFARM_ERR_INVALID_ARGUMENT);
	}
	if (strchr(dname, '/') != NULL) {
		gflog_debug(GFARM_MSG_1001746,
			"argument 'dname' is invalid");
		return (GFARM_ERR_INVALID_ARGUMENT);
	}

	e = inode_lookup_by_name(ddir, dname, process, 0, &dst);
	if (e == GFARM_ERR_NO_ERROR) {
		if (GFARM_S_ISDIR(inode_get_mode(src)) ==
		    GFARM_S_ISDIR(inode_get_mode(dst))) {
			e = inode_unlink(ddir, dname, process);
			if (e != GFARM_ERR_NO_ERROR) {
				gflog_debug(GFARM_MSG_1001747,
					"inode_unlink() failed: %s",
					gfarm_error_string(e));
				return (e);
			}
		} else if (GFARM_S_ISDIR(inode_get_mode(src))) {
			gflog_debug(GFARM_MSG_1001748,
				"inode 'inode_get_mode(src)' "
				"is not a directory");
			return (GFARM_ERR_NOT_A_DIRECTORY);
		} else {
			gflog_debug(GFARM_MSG_1001749,
				"inode 'inode_get_mode(src)' is directory");
			return (GFARM_ERR_IS_A_DIRECTORY);
		}
	} else if (e != GFARM_ERR_NO_SUCH_FILE_OR_DIRECTORY)
		return (e);

	e = inode_create_link_internal(ddir, dname, user, src);
	if (e != GFARM_ERR_NO_ERROR) {
		gflog_error(GFARM_MSG_1000319,
		    "rename(%s, %s): failed to link: %s",
		    sname, dname, gfarm_error_string(e));
		return (e);
	}
	e = inode_lookup_relative(sdir, sname, GFS_DT_UNKNOWN, INODE_REMOVE,
	    user, 0, NULL, &src, NULL);
	if (e != GFARM_ERR_NO_ERROR)
		gflog_error(GFARM_MSG_1000320,
		    "rename(%s, %s): failed to unlink: %s",
		    sname, dname, gfarm_error_string(e));

	return (e);
}
