unmount_all(void)
{
	fprintf(stderr, "Attempting to unmount all filesystems:\n");

	while (mount_list) {
		fprintf(stderr, "\tUnmounting: %s\n", mount_list->root_name);

		do_umount(mount_list);
	}

	fprintf(stderr, "done.\n");
}
