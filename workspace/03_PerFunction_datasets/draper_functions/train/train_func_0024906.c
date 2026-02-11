advance_one_block(FILE* file)
{
	gint len = BSIZE;
	gchar buffer[BSIZE];

	while(!feof(file))
	{
		if(!fgets(buffer,len,file)) return 0;
		if(strstr(buffer,"Title")) return 1;
	}
	return -1;
}
