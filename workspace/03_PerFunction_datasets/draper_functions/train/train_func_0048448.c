do_get_size(int argc, char **argv)
{
	ext2_ino_t	size;

	if (check_icount(argv[0]))
		return;
	size = ext2fs_get_icount_size(test_icount);
	printf("Size of icount is: %lu\n", (unsigned long)size);
}
