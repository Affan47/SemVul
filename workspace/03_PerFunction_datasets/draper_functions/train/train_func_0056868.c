ce_match_stat_basic(struct cache_entry *ce, struct stat *st)
{
	unsigned int changed = 0;

	switch (ntohl(ce->ce_mode) & S_IFMT) {
	case S_IFREG:
		changed |= !S_ISREG(st->st_mode) ? TYPE_CHANGED : 0;


		if (trust_executable_bit &&
		    (0100 & (ntohl(ce->ce_mode) ^ st->st_mode)))
			changed |= MODE_CHANGED;
		break;
	case S_IFLNK:
		if (!S_ISLNK(st->st_mode) &&
		    (has_symlinks || !S_ISREG(st->st_mode)))
			changed |= TYPE_CHANGED;
		break;
	case S_IFGITLINK:
		if (!S_ISDIR(st->st_mode))
			changed |= TYPE_CHANGED;
		else if (ce_compare_gitlink(ce))
			changed |= DATA_CHANGED;
		return changed;
	default:
		die("internal error: ce_mode is %o", ntohl(ce->ce_mode));
	}
	if (ce->ce_mtime.sec != htonl(st->st_mtime))
		changed |= MTIME_CHANGED;
	if (ce->ce_ctime.sec != htonl(st->st_ctime))
		changed |= CTIME_CHANGED;

#ifdef USE_NSEC


	if (ce->ce_mtime.nsec != htonl(st->st_mtim.tv_nsec))
		changed |= MTIME_CHANGED;
	if (ce->ce_ctime.nsec != htonl(st->st_ctim.tv_nsec))
		changed |= CTIME_CHANGED;
#endif

	if (ce->ce_uid != htonl(st->st_uid) ||
	    ce->ce_gid != htonl(st->st_gid))
		changed |= OWNER_CHANGED;
	if (ce->ce_ino != htonl(st->st_ino))
		changed |= INODE_CHANGED;

#ifdef USE_STDEV


	if (ce->ce_dev != htonl(st->st_dev))
		changed |= INODE_CHANGED;
#endif

	if (ce->ce_size != htonl(st->st_size))
		changed |= DATA_CHANGED;

	return changed;
}
