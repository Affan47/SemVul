kernel_variable_init(void)
{
	char fname[] = "/tmp/efi.XXXXXX";
	char cmdline[256];
	int fd, ret;
	struct stat st;
	char *buf;

	if (kernel_efi_path)
		return;
	mktemp(fname);
	snprintf(cmdline, sizeof(cmdline), "mount -l > %s", fname);
	ret = system(cmdline);
	if (WEXITSTATUS(ret) != 0)

		exit(1);
	fd = open(fname, O_RDONLY);
	unlink(fname);
	if (fd < 0) {
		fprintf(stderr, "Failed to open output of %s\n", cmdline);
		exit(1);
	}
	if (fstat(fd, &st) < 0) {
		perror("stat failed");
		exit(1);
	}
	if (st.st_size == 0) {
		fprintf(stderr, "No efivarfs filesystem is mounted\n");
		exit(1);
	}
	buf = malloc(st.st_size);
	read(fd, buf, st.st_size);
	close(fd);

	char *ptr = buf;
	char path[512], type[512];
	while (ptr < buf + st.st_size) {
		int count;

		sscanf(ptr, "%*s on %s type %s %*s\n%n", path, type, &count);
		ptr += count;
		if (strcmp(type, "efivarfs") == 0)
			break;
	}
	if (strcmp(type, "efivarfs") != 0) {
		fprintf(stderr, "No efivarfs filesystem is mounted\n");
		exit(1);
	}
	kernel_efi_path = malloc(strlen(path) + 1);
	strcpy(kernel_efi_path, path);
}
