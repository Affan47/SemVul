load_firmware(const char *firmware, const char *sysfs_path)
{
	int cnt;
	int firmware_fd, loading_fd;


	xchdir("/lib/firmware");
	firmware_fd = open(firmware, O_RDONLY);


	xchdir(sysfs_path);
	for (cnt = 0; cnt < 30; ++cnt) {
		loading_fd = open("loading", O_WRONLY);
		if (loading_fd >= 0)
			goto loading;
		sleep(1);
	}
	goto out;

 loading:
	cnt = 0;
	if (firmware_fd >= 0) {
		int data_fd;


		if (full_write(loading_fd, "1", 1) != 1)
			goto out;


		data_fd = open("data", O_WRONLY);
		if (data_fd < 0)
			goto out;
		cnt = bb_copyfd_eof(firmware_fd, data_fd);
		if (ENABLE_FEATURE_CLEAN_UP)
			close(data_fd);
	}


	if (cnt > 0)
		full_write(loading_fd, "0", 1);
	else
		full_write(loading_fd, "-1", 2);

 out:
	xchdir("/dev");
	if (ENABLE_FEATURE_CLEAN_UP) {
		close(firmware_fd);
		close(loading_fd);
	}
}
