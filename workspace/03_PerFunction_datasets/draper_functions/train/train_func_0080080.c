print_file_info(struct file_info *info)
{
	int i;

	printf("file: %s, size: %" GFARM_PRId64 "\n",
	       info->pathname, info->filesize);
	printf("ncopy = %d\n", info->ncopy);
	for (i = 0; i < info->ncopy; ++i)
		printf("%s\n", info->copy[i]);
	fflush(stdout);
}
