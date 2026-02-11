fsetflags (const char * name, unsigned long flags)
{
	struct stat buf;
#if HAVE_CHFLAGS && !(APPLE_DARWIN && HAVE_EXT2_IOCTLS)
	unsigned long bsd_flags = 0;

#ifdef UF_IMMUTABLE
	if (flags & EXT2_IMMUTABLE_FL)
		bsd_flags |= UF_IMMUTABLE;
#endif
#ifdef UF_APPEND
	if (flags & EXT2_APPEND_FL)
		bsd_flags |= UF_APPEND;
#endif
#ifdef UF_NODUMP
	if (flags & EXT2_NODUMP_FL)
		bsd_flags |= UF_NODUMP;
#endif

	return chflags (name, bsd_flags);
#else
#if HAVE_EXT2_IOCTLS
	int fd, r, f, save_errno = 0;

	if (!lstat(name, &buf) &&
	    !S_ISREG(buf.st_mode) && !S_ISDIR(buf.st_mode)) {
		goto notsupp;
	}
#if !APPLE_DARWIN
	fd = open (name, OPEN_FLAGS);
	if (fd == -1)
		return -1;
	f = (int) flags;
	r = ioctl (fd, EXT2_IOC_SETFLAGS, &f);
	if (r == -1)
		save_errno = errno;
	close (fd);
	if (save_errno)
		errno = save_errno;
#else
   f = (int) flags;
   return syscall(SYS_fsctl, name, EXT2_IOC_SETFLAGS, &f, 0);
#endif
	return r;
#endif
#endif
notsupp:
	errno = EOPNOTSUPP;
	return -1;
}
