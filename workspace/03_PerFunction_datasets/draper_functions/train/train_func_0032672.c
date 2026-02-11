gf_cache_check_if_cache_file_is_corrupted(const DownloadedCacheEntry entry) {

	FILE *the_cache = gf_f64_open ( entry->cache_filename, "rb" );
	if ( the_cache )
	{
		char * endPtr;
		const char * keyValue = gf_cfg_get_key ( entry->properties, CACHE_SECTION_NAME, CACHE_SECTION_NAME_CONTENT_SIZE );

		gf_f64_seek ( the_cache, 0, SEEK_END );
		entry->cacheSize = ( u32 ) gf_f64_tell ( the_cache );
		fclose ( the_cache );
		if (keyValue) {
			entry->contentLength = strtoul( keyValue, &endPtr, 10);
			if (*endPtr!='\0' || entry->contentLength != entry->cacheSize) {
				entry->flags |= CORRUPTED;
				GF_LOG(GF_LOG_INFO, GF_LOG_NETWORK, ("[CACHE] gf_cache_create_entry:%d, Cache corrupted: file and cache info size mismatch.\n", __LINE__));
			}
		} else {
			entry->flags |= CORRUPTED;
			GF_LOG(GF_LOG_INFO, GF_LOG_NETWORK, ("[CACHE] gf_cache_create_entry:%d, CACHE is corrupted !\n", __LINE__));
		}
	} else {
		entry->flags |= CORRUPTED;
	}
	return entry->flags & CORRUPTED;
}
