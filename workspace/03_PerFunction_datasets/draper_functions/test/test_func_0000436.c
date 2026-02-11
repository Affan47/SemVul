dblayer_select_ncache(size_t cachesize, int *ncachep)
{


	if (*ncachep) {
		return;
	}


#if defined(__LP64__) || defined (_LP64)
	if ( (sizeof(cachesize) > 4) && (cachesize > (4L * GIGABYTE))) {
		*ncachep = (cachesize / (4L * GIGABYTE)) + 1;
		LDAPDebug(LDAP_DEBUG_ANY,"Setting ncache to: %d to keep each chunk below 4Gbytes\n",
			*ncachep, 0, 0);
	}
#endif


#if defined(_WIN32)
	{
		size_t max_windows_chunk = (300 * MEGABYTE);
		if (cachesize > max_windows_chunk) {
			*ncachep = (cachesize / max_windows_chunk) + 1;
			LDAPDebug(LDAP_DEBUG_ANY,"Setting ncache to: %d for Windows memory address space fragmentation\n",
                *ncachep, 0, 0);
		}
	}
#endif
}
