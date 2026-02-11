get_filter_prog(const char *content_type)
{
	char *filterprog, *p;
	const char *dummy;


	filterprog=courier_malloc(strlen(content_type)
				  +sizeof(FILTERBINDIR)+20);

	strcpy(filterprog, FILTERBINDIR "/");

	p=filterprog+sizeof(FILTERBINDIR);
	for (dummy=content_type; *dummy; dummy++)
	{
		*p++ = *dummy == '.' || *dummy == '/' ? '-':*dummy;
	}
	*p=0;
	strcat(filterprog, ".filter");

	if (access(filterprog, X_OK) < 0)
	{
		free(filterprog);
		filterprog=NULL;
	}
	return (filterprog);
}
