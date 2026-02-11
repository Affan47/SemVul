xfs_chattr( XfsCookie *fc, int16 attr )
{
	char fpathName[MAXPATHNAMELEN];
	cookie2Pathname(fc, NULL, fpathName);

	D(bug("HOSTFS: fs_chattr (%s)", fpathName));


	struct stat statBuf;
    if ( lstat( fpathName, &statBuf ) )
		return errnoHost2Mint( errno, TOS_EACCDN );

    mode_t newmode;
    if ( attr & 0x01 )
		newmode = statBuf.st_mode & ~( S_IWUSR | S_IWGRP | S_IWOTH );
    else
		newmode = statBuf.st_mode | ( S_IWUSR | S_IWGRP | S_IWOTH );
    if ( newmode != statBuf.st_mode &&
		 chmod( fpathName, newmode ) )
		return errnoHost2Mint( errno, TOS_EACCDN );

	return TOS_E_OK;
}
