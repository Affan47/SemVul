swan_calculate_md5sum(const char *pkg_path, int pkg_fd, char *md5sum)
{
	int ret;

	memset(md5sum, 0, MD5SUM_LEN);

	ret = swan_write_md5sum(pkg_fd, md5sum);
	if (ret < 0)
	{
		error_msg("write");
		return ret;
	}

	ret = calculate_file_md5sum(pkg_path, md5sum);
	if (ret < 0)
	{
		error_msg("calculate_file_md5sum");
		return ret;
	}

	println("md5sum = %s", text_header(md5sum, MD5SUM_LEN));

	return 0;
}
