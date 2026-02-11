freeflist(void)
{
	int	cnt;

	for  (cnt = 0;  cnt < f_num;  cnt++)
		if  (flist[cnt].f_issep)
			free((char *) flist[cnt].f_field);
	free((char *) flist);
}
