gfarm_name_submatch(const char *pattern, const char *name, int namelen,
	int flags)
{
	int w;

	for (; --namelen >= 0; name++, pattern++){
		if (*pattern == '?')
			continue;
		if (*pattern == '[' &&
		    gfarm_pattern_charset_parse(pattern, 1, &w)) {
			if (gfarm_pattern_charset_match(pattern + 1, w - 1,
			    *(unsigned char *)name)) {
				pattern += w;
				continue;
			}
			return (0);
		}
		if ((flags & GFARM_PATTERN_NOESCAPE)== 0 && *pattern == '\\') {
			if (pattern[1] != '\0' &&
			    ((flags & GFARM_PATTERN_PATHNAME) == 0 ||
			     pattern[1] != '/')) {
				if (*name == pattern[1]) {
					pattern++;
					continue;
				}
			}
		}
		if (*name != *pattern)
			return (0);
	}
	return (1);
}
