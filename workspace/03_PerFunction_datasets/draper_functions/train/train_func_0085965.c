dos_showfat(direntry_t *entry, MainParam_t *mp)
{
	Stream_t *File=mp->File;
	Arg_t *arg = (Arg_t *) mp->arg;
	fprintPwd(stdout, entry,0);
	putchar(' ');
	if(arg->offset == -1) {
		printFat(File);
	} else {
		printFatWithOffset(File, arg->offset);
	}
	printf("\n");
	return GOT_ONE;
}
