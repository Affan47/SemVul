pcache_init(void)
{
	int h;
	char *lang = NULL;

	ZERO(&pong_cache);
	ZERO(&recent_pongs);


	udp_pings = aging_make(UDP_PING_FREQ,
			host_addr_hash_func, host_addr_eq_func, wfree_host_addr);


	local_meta.flags = PONG_META_HAS_VC | PONG_META_HAS_DU;
	memcpy(local_meta.vendor, "GTKG", 4);
	local_meta.version_ua = version_get_code();
	local_meta.version_up = 0x2;


	(void) lang;

#if 0


#define GET_LANG(x)										\
G_STMT_START {											\
	if (lang == NULL) {									\
		lang = getenv(#x);								\
		if (lang != NULL) {								\
			if (strlen(lang) >= 3 && lang[2] != '_')	\
				lang = NULL;							\
		}												\
	}													\
} G_STMT_END

	GET_LANG(LANG);
	GET_LANG(LC_CTYPE);
	GET_LANG(LC_MESSAGES);
	GET_LANG(LC_ALL);

#undef GET_LANG

	if (lang != NULL) {
		int len = strlen(lang);

		if (len > 0) {
			int i;

			local_meta.flags |= PONG_META_HAS_LOC;

			if (len == 1)
				memcpy(local_meta.language, "en", 2);
			else
				memcpy(local_meta.language, lang, 2);

			for (i = 0; i < 2; i++)
				local_meta.language[i] = ascii_tolower(local_meta.language[i]);

			if (len >= 5 && lang[2] == '_') {
				memcpy(local_meta.country, lang + 3, 2);
				for (i = 0; i < 2; i++)
					local_meta.country[i] = ascii_toupper(local_meta.country[i]);
			} else
				local_meta.country[0] = '\0';
		}

		g_info("locale set to language=\"%.2s\", country=\"%.2s\"",
			local_meta.language, local_meta.country);
	} else
		g_warning("unable to figure out locale preferences");
#endif

	for (h = 0; h < PONG_CACHE_SIZE; h++)
		pong_cache[h].hops = h;

	recent_pongs[HOST_ANY].hs_recent_pongs =
		hset_create_any(cached_pong_hash, NULL, cached_pong_eq);

	recent_pongs[HOST_ULTRA].hs_recent_pongs =
		hset_create_any(cached_pong_hash, NULL, cached_pong_eq);
}
