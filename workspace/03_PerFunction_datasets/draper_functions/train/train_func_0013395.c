compute_base (char *path)
{
	char *p = strrchr (path, '/');
	if (p == NULL)
		return NULL;


	if (strcmp (p, "/mono") && strcmp (p, "/mono-boehm") && strcmp (p, "/mono-sgen") && strcmp (p, "/pedump") && strcmp (p, "/monodis"))
		return NULL;

	*p = 0;
	p = strrchr (path, '/');
	if (p == NULL)
		return NULL;

	if (strcmp (p, "/bin") != 0)
		return NULL;
	*p = 0;
	return path;
}
