sfnfromsurl (char *surl)
{
	char *p;

	if (strncmp (surl, "srm://", 6)) {
		errno = EINVAL;
		return (NULL);
	}
	if ((p = strstr (surl + 6, "?SFN=")))
		return (p + 5);
	if ((p = strchr (surl + 6, '/')) == NULL) {
		errno = EINVAL;
		return (NULL);
	}
	return (p);
}
