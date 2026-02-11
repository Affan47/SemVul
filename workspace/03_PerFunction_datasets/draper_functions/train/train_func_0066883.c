findConfLineNumber(int nr)
{
	struct wordcount *filelist = files;
	for(; filelist->next && (filelist->max < nr); filelist = filelist->next);
	return filelist;
}
