cgethostbyaddr(addr, len, type)
	const char *addr;
	int len;
	int type;
{
	const char *function = "cgethostbyaddr()";
	static struct {
		unsigned			allocated:1;
		in_addr_t			addr;
		time_t				written;
		struct hostent		hostent;
	} table[SOCKD_ADDRESSCACHE], *freehost;
	static unsigned long int hit, miss, count;
	const time_t timenow = time(NULL);

	const int hashi
	= addrhash(((const struct in_addr *)addr)->s_addr, ELEMENTS(table));
	size_t i;
	struct hostent *hostent;

#if SOCKD_CACHESTAT
	if (++count % SOCKD_CACHESTAT == 0)
		slog(LOG_INFO, "%s: hit: %d, miss: %d", function, hit, miss);
#endif

	for (i = hashi, freehost = NULL; i < ELEMENTS(table); ++i) {
		if (!table[i].allocated) {
			if (freehost == NULL)
				freehost = &table[i];
			continue;
		}


		if (table[i].addr == ((const struct in_addr *)addr)->s_addr) {
			if (difftime(timenow, table[i].written) >= SOCKD_CACHETIMEOUT) {
				freehost = &table[i];
				break;
			}
			++hit;
			return &table[i].hostent;
		}
	}
	++miss;

	if ((hostent = gethostbyaddr(addr, len, type)) == NULL)
		return NULL;

	if (freehost == NULL)
		for (i = hashi, freehost = &table[i]; i < ELEMENTS(table); ++i) {
			if (difftime(timenow, table[i].written) >= SOCKD_CACHETIMEOUT) {
				freehost = &table[i];
				break;
			}

			if (freehost->written < table[i].written) {
				freehost = &table[i];
				break;
			}
		}

	if (hostentupdate(&freehost->hostent, hostent) == NULL) {
		freehost->allocated = 0;
		slog(LOG_WARNING, "%s: %s", NOMEM, function);
		return NULL;
	}


	freehost->addr = ((const struct in_addr *)addr)->s_addr;
	time(&freehost->written);
	freehost->allocated = 1;

	return &freehost->hostent;
}
