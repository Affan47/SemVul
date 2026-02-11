swan_write_version(const char *system_mnt_point, u32 version)
{
	ssize_t writelen;
	char buff[128];
	char version_file[1024];

	text_path_cat(version_file, sizeof(version_file), system_mnt_point, SWAN_VERSION_PATH);

	writelen = value2text_base(version, buff, 0, 0, 16) - buff;
	writelen = file_writeto(version_file, buff, writelen, 0, O_TRUNC);
	if (writelen < 0)
	{
		error_msg("write version failed");
	}

	return writelen;
}
