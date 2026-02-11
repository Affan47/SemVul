xfs_stat64( XfsCookie *fc, memptr statp )
{
	char fpathName[MAXPATHNAMELEN];
	cookie2Pathname(fc, NULL, fpathName);

	D(bug("HOSTFS: fs_stat64 (%s)", fpathName));


	struct stat statBuf;
	int32 res = host_stat64(fc, fpathName, &statBuf);
	if ( res != TOS_E_OK )
		return res;

	  WriteInt32( statp     , WHEN_INT4B( 0, ( statBuf.st_dev >> 32 ) & 0xffffffffUL ) );
	  WriteInt32( statp +  4, statBuf.st_dev & 0xffffffffUL );
	  WriteInt32( statp +  8, statBuf.st_ino );
	  WriteInt32( statp + 12, modeHost2Mint(statBuf.st_mode) );
	  WriteInt32( statp + 16, statBuf.st_nlink );
	  WriteInt32( statp + 20, statBuf.st_uid );
	  WriteInt32( statp + 24, statBuf.st_gid );
	  WriteInt32( statp + 28, WHEN_INT4B( 0, ( statBuf.st_rdev >> 32 ) & 0xffffffffUL ) );
	  WriteInt32( statp + 32,   statBuf.st_rdev & 0xffffffffUL );

	 WriteInt32( statp + 36, 0 );
	 WriteInt32( statp + 40,   statBuf.st_atime );
	 WriteInt32( statp + 44, 0 );
	 WriteInt32( statp + 48, 0 );
	 WriteInt32( statp + 52,   statBuf.st_mtime );
	 WriteInt32( statp + 56, 0 );
	 WriteInt32( statp + 60, 0 );
	 WriteInt32( statp + 64,   statBuf.st_ctime );
	 WriteInt32( statp + 68, 0 );

	  WriteInt32( statp + 72, ( statBuf.st_size >> 32 ) & 0xffffffffUL );
	  WriteInt32( statp + 76,   statBuf.st_size & 0xffffffffUL );
#if defined(OS_beos) || defined(__MINGW32__)
	  WriteInt32( statp + 80,   0 );
	  WriteInt32( statp + 84,   0 );
	  WriteInt32( statp + 88,   0 );
#else
	  WriteInt32( statp + 80, ( statBuf.st_blocks >> 32 ) & 0xffffffffUL );
	  WriteInt32( statp + 84,   statBuf.st_blocks & 0xffffffffUL );
	  WriteInt32( statp + 88,   statBuf.st_blksize );
#endif
	  WriteInt32( statp + 92,   0 );
	  WriteInt32( statp + 96,   0 );

	D(bug("HOSTFS: fs_stat64 mode %#02x, mtime %#08lx", modeHost2Mint(statBuf.st_mode), ReadInt32(statp + 52)));

	return TOS_E_OK;
}
