com_get (char *arg)
{
	unsigned long long amount_written;
	char newpath[255];

	if ((server==NULL) || (vol==NULL)) {
		printf("You're not connected yet to a volume\n");
		goto error;
	}
	if ((arg[0]=='-') && (arg[1]=='r') && (arg[2]==' ')) {
		arg+=3;
		while ((arg) && (isspace(arg[0]))) arg++;
		snprintf(newpath,255,"%s/%s",curdir,arg);
		return recursive_get(newpath);
	} else
		return com_get_file(arg,0, &amount_written);
error:
	return -1;
}
