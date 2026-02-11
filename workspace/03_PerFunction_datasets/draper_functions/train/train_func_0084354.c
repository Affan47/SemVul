get_header_val(const char *hname, mpg123_string *response)
{
	char *tmp = NULL;
	size_t prelen = strlen(hname);

	if(!strncasecmp(hname, response->p, prelen) && (response->p[prelen] == ':'))
	{
		++prelen;
		if((tmp = strchr(response->p, '\r')) != NULL ) tmp[0] = 0;
		if((tmp = strchr(response->p, '\n')) != NULL ) tmp[0] = 0;
		tmp = response->p+prelen;

		while((tmp[0] == ' ') || (tmp[0] == '\t'))
		{
			++tmp;
		}
	}
	return tmp;
}
