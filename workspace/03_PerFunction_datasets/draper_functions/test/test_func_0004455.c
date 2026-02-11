g_create(const char *filename)
{
	struct libmail_kwGenericEntry *e=
		malloc(sizeof (struct libmail_kwGenericEntry));
	char *p;

	if (e && (e->filename=strdup(filename)) == NULL)
	{
		free(e);
		e=NULL;
	}

	if (!e)
		return NULL;

	e->keywords=NULL;

	if ((p=strrchr(e->filename, MDIRSEP[0])) != 0)
		*p=0;
	return e;
}
