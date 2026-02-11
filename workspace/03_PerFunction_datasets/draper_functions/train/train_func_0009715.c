gfm_server_setxattr(struct peer *peer, int from_client, int skip, int xmlMode)
{
	gfarm_error_t e;
	const char *diag =
	    xmlMode ? "GFM_PROTO_XMLATTR_SET" : "GFM_PROTO_XATTR_SET";
	char *attrname = NULL;
	size_t size;
	char *value = NULL;
	int flags;
	struct process *process;
	gfarm_int32_t fd;
	struct inode *inode;
	struct db_waitctx ctx, *waitctx;
	int addattr;

	e = gfm_server_get_request(peer, diag,
	    "sBi", &attrname, &size, &value, &flags);
	if (e != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1002070,
			"gfm_server_get_request() failure:%s",
			gfarm_error_string(e));
		return (e);
	}
	if (skip) {
		free(attrname);
		return (GFARM_ERR_NO_ERROR);
	}
	if (xmlMode) {
		waitctx = &ctx;
#ifdef ENABLE_XMLATTR
		if (value[size-1] != '\0') {
			e = GFARM_ERR_INVALID_ARGUMENT;
			gflog_debug(GFARM_MSG_1002071,
				"argument 'xmlMode' is invalid");
			goto quit;
		}
#else
		e = GFARM_ERR_OPERATION_NOT_SUPPORTED;
		gflog_debug(GFARM_MSG_1002072,
			"operation is not supported(xmlMode)");
		goto quit;
#endif
	} else
		waitctx = NULL;

	db_waitctx_init(waitctx);
	giant_lock();
	if ((process = peer_get_process(peer)) == NULL) {
		gflog_debug(GFARM_MSG_1002073,
			"peer_get_process() failed");
		e = GFARM_ERR_OPERATION_NOT_PERMITTED;
	} else if ((e = peer_fdpair_get_current(peer, &fd)) !=
	    GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1002074,
			"peer_fdpair_get_current() failed: %s",
			gfarm_error_string(e));
	} else if ((e = process_get_file_inode(process, fd, &inode)) !=
	    GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1002075,
			"process_get_file_inode() failed: %s",
			gfarm_error_string(e));
	} else if ((e = inode_access(inode, process_get_user(process),
			GFS_W_OK)) != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1002076,
			"inode_access() failed: %s",
			gfarm_error_string(e));
	} else
		e = setxattr(xmlMode, inode, attrname, value, size,
				flags, waitctx, &addattr);
	giant_unlock();

	if (e == GFARM_ERR_NO_ERROR) {
		e = dbq_waitret(waitctx);
		if (e == GFARM_ERR_NO_ERROR) {
			giant_lock();
			inode_status_changed(inode);
			giant_unlock();
		} else if (addattr) {
			giant_lock();
			inode_xattr_remove(inode, xmlMode, attrname);
			giant_unlock();
		}
	}
	db_waitctx_fini(waitctx);
quit:
	free(value);
	free(attrname);
	return (gfm_server_put_reply(peer, diag, e, ""));
}
