GetHostByName(char *Name)
{
	char *RetCode = NULL;
	struct hostent *hp = NULL;


	if ((hp = gethostbyname(Name)) != NULL)
	{
		if ((RetCode = (char*) calloc(strlen(hp->h_name)+1,sizeof(char))) ==NULL)
			return NULL;

		strcpy(RetCode,hp->h_name);
	}

	return RetCode;
}
