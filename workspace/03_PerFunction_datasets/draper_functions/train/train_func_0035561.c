swan_write_md5sum(int pkg_fd, char *md5sum)
{
	int ret;

	ret = lseek(pkg_fd, MEMBER_OFFSET(struct swan_file_info, md5sum), SEEK_SET);
	if (ret < 0)
	{
		print_error("lseek");
		return ret;
	}

	ret = ffile_write(pkg_fd, md5sum, MD5SUM_LEN);
	if (ret < MD5SUM_LEN)
	{
		print_error("ffile_write");
		return ret;
	}

	fsync(pkg_fd);

	return 0;
}
