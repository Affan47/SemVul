open_mmfile(const char *name, struct stat *sb)
{
	int	result;
	if  ((result = open(mmfile_name(name), O_RDONLY)) < 0)
		return  -1;
	fstat(result, sb);
	return  result;
}
