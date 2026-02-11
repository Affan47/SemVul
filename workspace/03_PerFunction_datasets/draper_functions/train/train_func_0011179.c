symlink_err(void)
{
    if (errno == EACCES || errno == EPERM)
	return NFS3ERR_ACCES;
    else if (is_stale())
	return NFS3ERR_STALE;
    else if (errno == EROFS)
	return NFS3ERR_ROFS;
    else if (errno == EEXIST)
	return NFS3ERR_EXIST;
    else if (errno == ENOSPC)
	return NFS3ERR_NOSPC;
#ifdef EDQUOT
    else if (errno == EDQUOT)
	return NFS3ERR_DQUOT;
#endif
    else if (errno == ENOSYS)
	return NFS3ERR_NOTSUPP;
    else if (errno == EINVAL)
	return NFS3ERR_INVAL;
    else
	return NFS3ERR_IO;
}
