is_ok_ascii (const char *s)
{
	const char *p;
	for (p = s; *p != '\0'; p++) {
		if ( ! ( (*p >= 'a' && *p <= 'z') ||
			 (*p >= 'A' && *p <= 'Z') ||
			 (*p >= '0' && *p <= '9') ||
			 strchr ("():,.[] !?~+-_{}/=><*^'\"", *p) != NULL) ) {
			return FALSE;
		}
	}
	return TRUE;
}
