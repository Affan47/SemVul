sp_file_exists(const char *filename)
{
	SP_STAT stat;
	if(sp_stat(filename,&stat) && sp_isreg(&stat)) return -1;
	return 0;
}
