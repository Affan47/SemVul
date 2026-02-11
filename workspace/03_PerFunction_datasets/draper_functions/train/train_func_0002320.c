fill_stat_cache_info(struct cache_entry *ce, struct stat *st)
{
	ce->ce_ctime.sec = htonl(st->st_ctime);
	ce->ce_mtime.sec = htonl(st->st_mtime);
#ifdef USE_NSEC
	ce->ce_ctime.nsec = htonl(st->st_ctim.tv_nsec);
	ce->ce_mtime.nsec = htonl(st->st_mtim.tv_nsec);
#endif
	ce->ce_dev = htonl(st->st_dev);
	ce->ce_ino = htonl(st->st_ino);
	ce->ce_uid = htonl(st->st_uid);
	ce->ce_gid = htonl(st->st_gid);
	ce->ce_size = htonl(st->st_size);

	if (assume_unchanged)
		ce->ce_flags |= htons(CE_VALID);
}
