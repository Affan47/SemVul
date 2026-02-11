get_shared_file_name(struct seg_info *htlb_seg_info, char *file_path)
{
	int ret;
	char binary[PATH_MAX+1];
	char *binary2;

	memset(binary, 0, sizeof(binary));
	ret = readlink("/proc/self/exe", binary, PATH_MAX);
	if (ret < 0) {
		WARNING("shared_file: readlink() on /proc/self/exe "
		      "failed: %s\n", strerror(errno));
		return -1;
	}

	binary2 = basename(binary);
	if (!binary2) {
		WARNING("shared_file: basename() on %s failed: %s\n",
		      binary, strerror(errno));
		return -1;
	}

	assemble_path(file_path, "%s/%s_%zd_%d", share_readonly_path, binary2,
		      sizeof(unsigned long) * 8, htlb_seg_info->index);

	return 0;
}
