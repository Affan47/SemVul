freespace(const char *ptr,
	unsigned long *tblocks, unsigned long *nblocks,
	unsigned long *tinodes, unsigned long *ninodes,
	unsigned *blksize)
{
#if HAVE_STATVFS
struct statvfs buf;

	if (statvfs(ptr, &buf))	return (-1);

#define	BTOTAL buf.f_blocks
#define	BAVAIL buf.f_bavail
#define	ITOTAL buf.f_files
#define	IAVAIL buf.f_favail

	*blksize=buf.f_bsize;

#else
#if HAVE_STATFS
struct statfs buf;

	if (statfs(ptr, &buf))	return (-1);

#define	BTOTAL buf.f_blocks
#define	BAVAIL buf.f_bfree
#define	ITOTAL buf.f_files
#define	IAVAIL buf.f_ffree

	*blksize=buf.f_bsize;
#endif
#endif

	*tblocks= BTOTAL;
	*nblocks= BAVAIL;
	*tinodes= ITOTAL;
	*ninodes= IAVAIL;

	if (*tblocks != BTOTAL) *tblocks= ~0;
	if (*nblocks != BAVAIL) *nblocks= ~0;
	if (*tinodes != ITOTAL) *tinodes= ~0;
	if (*ninodes != IAVAIL) *ninodes= ~0;

	return (0);
}
