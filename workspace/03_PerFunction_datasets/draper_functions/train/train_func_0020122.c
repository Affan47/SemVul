inode_prepare_to_replicate(struct inode *inode, struct user *user,
	struct host *src, struct host *dst, gfarm_int32_t flags,
	struct file_replicating **frp)
{
	gfarm_error_t e;
	struct file_copy *copy;
	struct file_replicating *fr;

	if ((flags & ~GFS_REPLICATE_FILE_FORCE) != 0)
		return (GFARM_ERR_FUNCTION_NOT_IMPLEMENTED);

	if ((e = inode_check_file(inode)) != GFARM_ERR_NO_ERROR)
		return (e);


	if ((e = inode_access(inode, user, GFS_R_OK)) != GFARM_ERR_NO_ERROR)
		return (e);
	if (inode_is_creating_file(inode))
		return (GFARM_ERR_NO_SUCH_OBJECT);
	if (!inode_has_replica(inode, src))
		return (GFARM_ERR_NO_SUCH_OBJECT);
	if ((copy = inode_get_file_copy(inode, dst)) != NULL) {
		if (FILE_COPY_IS_VALID(copy))
			return (GFARM_ERR_ALREADY_EXISTS);
		else if (FILE_COPY_IS_BEING_REMOVED(copy))
			return (GFARM_ERR_DEVICE_BUSY);
		else
			return (GFARM_ERR_OPERATION_ALREADY_IN_PROGRESS);
	}
	if ((flags & GFS_REPLICATE_FILE_FORCE) == 0 &&
	    inode_is_opened_for_writing(inode))
		return (GFARM_ERR_FILE_BUSY);
	else if ((e = file_replicating_new(inode, dst, NULL, &fr)) !=
	    GFARM_ERR_NO_ERROR)
		return (e);

	*frp = fr;
	return (GFARM_ERR_NO_ERROR);
}
