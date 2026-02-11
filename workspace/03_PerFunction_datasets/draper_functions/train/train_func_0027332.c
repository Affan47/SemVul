swan_install(const char *dirpath)
{
	int ret;
	int fd;
	char busybox_path[1024];
	char pkg_path[1024];

	text_path_cat(busybox_path, sizeof(busybox_path), dirpath, "busybox.ext4");

	ret = file_mount_to(busybox_path, BUSYBOX_MOUNT_POINT, "ext4", 0, NULL);
	if (ret < 0)
	{
		error_msg("mount file \"%s\"", busybox_path);
		return ret;
	}

	text_path_cat(pkg_path, sizeof(pkg_path), dirpath, "upgrade.swan");

	fd = open(pkg_path, O_RDWR);
	if (fd < 0)
	{
		ret = fd;
		print_error("open upgrade file \"%s\" failed", pkg_path);
		goto out_umount_busybox;
	}

	ret = chroot(BUSYBOX_MOUNT_POINT);
	if (ret < 0)
	{
		print_error("chroot to " BUSYBOX_MOUNT_POINT " failed");
		goto out_close_fd;
	}

	ret = setenv("PATH", DEFAULT_PATH_VALUE, 1);
	if (ret < 0)
	{
		error_msg("setenv PATH failes");
		goto out_close_fd;
	}

	system_command("/etc/init.d/super_init.sh");

	print_mount_table();

	ret = fupgrade_simple(fd);

	system_command("/etc/init.d/super_deinit.sh");

out_close_fd:
	close(fd);
out_umount_busybox:
	umount_directory2(BUSYBOX_MOUNT_POINT, MNT_DETACH);

	return ret;
}
