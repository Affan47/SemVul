nm_dhcp_dhcpcd_get_path (const char *try_first)
{
	static const char *dhcpcd_paths[] = {
		"/sbin/dhcpcd",
		"/usr/sbin/dhcpcd",
		"/usr/pkg/sbin/dhcpcd",
		"/usr/local/sbin/dhcpcd",
		NULL
	};
	const char **path = dhcpcd_paths;

	if (strlen (try_first) && g_file_test (try_first, G_FILE_TEST_EXISTS))
		return try_first;

	while (*path != NULL) {
		if (g_file_test (*path, G_FILE_TEST_EXISTS))
			break;
		path++;
	}

	return *path;
}
