_is_scsi_cntrl(const char *path)
{
	uint64_t class;

	if (sysfs_enclosure_attached_to_cntrl(path) == 0)
		return 0;

	class = get_uint64(path, 0, "class");
	return (class & 0xff0000L) == 0x010000L;
}
