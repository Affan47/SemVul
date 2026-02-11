xfs_dev_close(ExtFile *fp, int16 pid)
{
	DUNUSED(pid);
	D(bug("HOSTFS:  dev_close (fd = %d, links = %d, pid = %d)", fp->hostFd, fp->links, pid));

	if ( fp->links <= 0 ) {
		if ( close( fp->hostFd ) )
			return errnoHost2Mint(errno,TOS_EIO);

		#if SIZEOF_INT != 4 || DEBUG_NON32BIT
			fdMapper.removeNative( fp->hostFd );
		#endif

	    D(bug("HOSTFS: /dev_close (fd = %d, %d)", fp->hostFd, pid));
	}

	return TOS_E_OK;
}
