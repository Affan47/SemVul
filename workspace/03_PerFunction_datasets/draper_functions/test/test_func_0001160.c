write_file(char *str)
{
	if(fprintf(fp, "%s", str) < 0){
		if(reopen_file() < 0)
			return -1;
		else
			return fprintf(fp, "%s", str);
	}

	return 0;

}
