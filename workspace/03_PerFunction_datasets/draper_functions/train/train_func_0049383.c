main(int argc, char *argv[])
{
	void *foo;
	char *test_file = (argc > 1) ? argv[1] : "/tmp/mmaptest.tmp";
	int rv, fd;


	errno = 0;
	foo = mmap(NULL, 65536, PROT_READ | PROT_WRITE,
		   MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

	printf("mmap() returned %p, errno = %d\n", foo, errno);
	if (foo == MAP_FAILED)
		return 1;

	rv = munmap(foo, 65536);
	printf("munmap() returned %d, errno = %d\n", rv, errno);
	if (rv)
		return 1;


	fd = open(test_file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0) {
		perror(test_file);
		return 1;
	}

	make_test_file(fd);


	foo = mmap(NULL, 65536, PROT_READ, MAP_SHARED, fd, 131072);
	printf("mmap() returned %p, errno = %d\n", foo, errno);
	if (foo == MAP_FAILED)
		return 1;

	if (*(unsigned long *)foo != 131072) {
		printf("mmap() with offset returned the wrong offset %ld!\n",
		       *(unsigned long *)foo);
		return 1;
	}

	if (munmap(foo, 65536)) {
		printf("munmap() returned nonzero, errno = %d\n", errno);
		return 1;
	}

	close(fd);
	unlink(test_file);

	return 0;
}
