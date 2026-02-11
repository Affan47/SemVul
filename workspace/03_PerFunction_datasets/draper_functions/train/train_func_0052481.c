print_download_info(gnet_fi_t handle, void *udata)
{
	struct gnutella_shell *sh = udata;
	gnet_fi_status_t status;
	gnet_fi_info_t *info;
	char buf[1024];

	shell_check(sh);

	info = guc_fi_get_info(handle);
	g_return_if_fail(info);
	guc_fi_get_status(handle, &status);

	str_bprintf(buf, sizeof buf, "ID: %s", guid_to_string(info->guid));
	shell_write(sh, buf);
	shell_write(sh, "\n");

	str_bprintf(buf, sizeof buf, "Filename: \"%s\"", info->filename);
	shell_write(sh, buf);
	shell_write(sh, "\n");

	str_bprintf(buf, sizeof buf, "Hash: %s",
		info->sha1 ? sha1_to_urn_string(info->sha1) : "<none>");
	shell_write(sh, buf);
	shell_write(sh, "\n");

	str_bprintf(buf, sizeof buf, "Status: %s",
		file_info_status_to_string(&status));
	shell_write(sh, buf);
	shell_write(sh, "\n");

	str_bprintf(buf, sizeof buf, "Size: %s",
		compact_size(status.size, GNET_PROPERTY(display_metric_units)));
	shell_write(sh, buf);
	shell_write(sh, "\n");

	str_bprintf(buf, sizeof buf, "Done: %u%% (%s)",
		filesize_per_100(status.size, status.done),
		compact_size(status.done, GNET_PROPERTY(display_metric_units)));
	shell_write(sh, buf);
	shell_write(sh, "\n");

	shell_write(sh, "--\n");
	guc_fi_free_info(info);
}
