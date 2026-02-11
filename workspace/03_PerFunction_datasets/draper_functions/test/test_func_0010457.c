check_read_access(char * pathname, char * cmd)
{
	char * access_array[BUFFERSIZE];
	int flag = 0;
	int i;

	parse(cmd, access_array);


	for (i = 0; access_array[i] != NULL && !flag; i++)
	{
		flag = (strcoll(pathname, access_array[i]) == 0);
	}

	return flag;
}
