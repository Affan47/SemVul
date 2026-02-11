rbd_dev_ondisk_valid(struct rbd_image_header_ondisk *ondisk)
{
	size_t size;
	u32 snap_count;


	if (memcmp(&ondisk->text, RBD_HEADER_TEXT, sizeof (RBD_HEADER_TEXT)))
		return false;


	if (ondisk->options.order < SECTOR_SHIFT)
		return false;


	if (ondisk->options.order > 8 * sizeof (int) - 1)
		return false;


	snap_count = le32_to_cpu(ondisk->snap_count);
	size = SIZE_MAX - sizeof (struct ceph_snap_context);
	if (snap_count > size / sizeof (__le64))
		return false;


	size -= snap_count * sizeof (__le64);
	if ((u64) size < le64_to_cpu(ondisk->snap_names_len))
		return false;

	return true;
}
