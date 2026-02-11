parse_vms_filespec(char *volume, char *directory, char *file)
{
    char *colon = strchr(file, ':');
    char *ptr = file;

    volume[0] = '\0';
    directory[0] = '\0';

    if (colon)
    {
	char saved = *(colon+1);
	*(colon+1) = '\0';
	strcpy(volume, file);
	ptr = colon+1;
	*ptr = saved;
    }

    char *enddir = strchr(ptr, ']');


    if (enddir && enddir[1] == '[')
	enddir=strchr(enddir+1, ']');

    if (*ptr == '[' && enddir)
    {
	char saved = *(enddir+1);

	*(enddir+1) = '\0';
	strcpy(directory, ptr);
	ptr = enddir+1;
	*ptr = saved;
    }


    if (ptr != file)
	memmove(file, ptr, strlen(ptr)+1);

}
