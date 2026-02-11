get_swan_board_type_by_system_img(const char *system_img)
{
	int ret;
	enum swan_board_type type;

	ret = file_mount_to(system_img, TEMP_MOUNT_POINT, "ext4", 0, NULL);
	if (ret < 0)
	{
		return SWAN_BOARD_UNKNOWN;
	}

	type = get_swan_board_type_by_build_prop(TEMP_MOUNT_POINT "/" BUILD_PROP_NAME);

	umount_directory2(TEMP_MOUNT_POINT, MNT_DETACH);

	return type;
}
