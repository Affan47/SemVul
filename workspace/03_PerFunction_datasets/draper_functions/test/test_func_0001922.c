pp_cached_file_stat_free(PP_CachedFileStat *cstat) {
	delete (Passenger::CachedFileStat *) cstat;
}
