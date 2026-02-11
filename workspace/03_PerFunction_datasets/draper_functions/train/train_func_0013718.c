xfs_dev_datime( ExtFile *fp, memptr datetimep, int16 wflag)
{
	char fpathName[MAXPATHNAMELEN];
	cookie2Pathname( &fp->fc, NULL, fpathName );

	D(bug("HOSTFS:  dev_datime (%s)", fpathName));
	struct stat statBuf;

	if ( stat(fpathName, &statBuf) )
		return errnoHost2Mint(errno,TOS_EFILNF);

	uint32 datetime = ReadInt32( datetimep );
	if (wflag != 0) {
		struct utimbuf tmb;

#if defined(USE_FS_EXT3)
		tmb.actime = datetime;
#else
		struct tm ttm;

		datetime2tm( datetime, &ttm );
		tmb.actime = mktime( &ttm );
#endif
		tmb.modtime = tmb.actime;

		utime( fpathName, &tmb );

#if ! defined(USE_FS_EXT3)
		D(bug("HOSTFS: /dev_datime: setting to: %d.%d.%d %d:%d.%d",
				  ttm.tm_mday,
				  ttm.tm_mon,
				  ttm.tm_year + 1900,
				  ttm.tm_sec,
				  ttm.tm_min,
				  ttm.tm_hour
				  ));
#endif
	}

#if ! defined(USE_FS_EXT3)
	datetime =
		( time2dos(statBuf.st_mtime) << 16 ) | date2dos(statBuf.st_mtime);
#endif
	WriteInt32( datetimep, datetime );

	return TOS_E_OK;
}
