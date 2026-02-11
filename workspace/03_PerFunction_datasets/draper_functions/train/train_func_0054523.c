os_mkdir(CHAR *dir, BOOL last_is_file)
{
	CHAR *tmp;
	CHAR *p;
	INT ret;

	tmp = os_new(CHAR, strlen(dir) + 3);
	strcpy(tmp, dir);

	for(p = tmp; *p; p++)
	{
		if(*p == '\\')
			*p = '/';
	}

	if(!last_is_file)
		strcat(tmp, "/");

	ret = ERR;
	for(p = tmp; *p; p++)
	{
		if(*p == '/')
		{
			*p = 0;
			mkdir(tmp, 0777);

			if(access(tmp, 06) == 0)
				ret = OK;
			else
				ret = ERR;

			*p = '/';

		}
	}
	return ret;

}
