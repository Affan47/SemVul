set_file_stats_(const char *filename, struct flac_stat_s *stats)
{
	struct utimbuf srctime;

	FLAC__ASSERT(0 != filename);
	FLAC__ASSERT(0 != stats);

	srctime.actime = stats->st_atime;
	srctime.modtime = stats->st_mtime;
	(void)flac_chmod(filename, stats->st_mode);
	(void)flac_utime(filename, &srctime);
#if !defined _MSC_VER && !defined __MINGW32__
	FLAC_CHECK_RETURN(chown(filename, stats->st_uid, -1));
	FLAC_CHECK_RETURN(chown(filename, -1, stats->st_gid));
#endif
}
