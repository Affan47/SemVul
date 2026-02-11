chroot_start(const char *path)
{
	if (chdir(path))
		fatal_with_errno(EXIT_FAILURE, "chdir(%s)", path);

	if (chroot(path))
		fatal_with_errno(EXIT_FAILURE, "chroot(%s)", path);

	if (chdir("/"))
		fatal_with_errno(EXIT_FAILURE, "chdir(/)");

	upsdebugx(1, "chrooted into %s", path);
}
