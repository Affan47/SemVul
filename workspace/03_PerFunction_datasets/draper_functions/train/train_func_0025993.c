copystat(stp, namep)
struct stat *stp;
namelist *namep;
{
	memset((char *)stp, 0, sizeof(*stp));

#ifndef	NODIRLOOP
	stp -> st_dev = (dev_t)-1;
	stp -> st_ino = (ino_t)-1;
#endif
	stp -> st_mode = namep -> st_mode;
	stp -> st_nlink = namep -> st_nlink;
#ifndef	NOUID
	stp -> st_uid = namep -> st_uid;
	stp -> st_gid = namep -> st_gid;
#endif
#ifdef	HAVEFLAGS
	stp -> st_flags = namep -> st_flags;
#endif
	stp -> st_size = namep -> st_size;
	memcpy((char *)&(stp -> st_atime),
		(char *)&(namep -> st_mtim), sizeof(stp -> st_atime));
	memcpy((char *)&(stp -> st_mtime),
		(char *)&(namep -> st_mtim), sizeof(stp -> st_mtime));
	memcpy((char *)&(stp -> st_ctime),
		(char *)&(namep -> st_mtim), sizeof(stp -> st_ctime));
#ifndef	NOSTBLKSIZE
	stp -> st_blksize = DEV_BSIZE;
#endif

	if (isdev(namep)) {
		stp -> st_size = (off_t)0;
		stp -> st_rdev = namep -> st_size;
	}
}
