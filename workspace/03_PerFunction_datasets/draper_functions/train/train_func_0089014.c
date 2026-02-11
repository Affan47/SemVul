escape_for_dn(char *src, char **dist)
{
	char *srcp = NULL;
	char *distp = NULL;
	char *dn = NULL;
	char *end = NULL;
	int rc = -1;

	if (NULL == dist) {
		return rc;
	}
	*dist = NULL;
	if (NULL == src) {
		return rc;
	}
	end = src + strlen(src);

	for (srcp = src; srcp && *srcp; srcp++) {
		for (dn = dnspecial; dn && *dn; dn++) {
			if (*srcp == *dn) {
				goto out;
			}
		}
	}
out:
	rc = 0;
	if (*srcp && (*srcp == *dn)) {
		char *distend = NULL;
		int maxdistlen = ((srcp - src) + (end - srcp) * 2) + 1;

		*dist =	(char *)PR_Calloc(sizeof(char), maxdistlen);
		if (NULL == *dist) {
			rc = -1;
			goto bail;
		}
		distend = *dist + maxdistlen;
		memcpy(*dist, src, srcp - src);
		distp = *dist + (srcp - src);
		put_dnescaped_char(&distp, &srcp);
		while (srcp && *srcp && distp && distp < distend) {
			for (dn = dnspecial; dn && *dn; dn++) {
				if (*srcp == *dn) {
					put_dnescaped_char(&distp, &srcp);
					break;
				}
			}
			if ('\0' == *dn) {
				*distp++ = *srcp++;
			}
		}
		if (distp == distend) {
			PR_Free(*dist);
			*dist = NULL;
			rc = -1;
		}
	}
bail:
	return rc;
}
