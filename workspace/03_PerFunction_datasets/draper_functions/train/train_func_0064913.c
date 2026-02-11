blkid_probe_set_dimension(blkid_probe pr,
		blkid_loff_t off, blkid_loff_t size)
{
	if (!pr)
		return -1;

	DBG(DEBUG_LOWPROBE, printf(
		"changing probing area pr=%p: size=%llu, off=%llu "
		"-to-> size=%llu, off=%llu\n",
		pr,
		(unsigned long long) pr->size,
		(unsigned long long) pr->off,
		(unsigned long long) size,
		(unsigned long long) off));

	pr->off = off;
	pr->size = size;
	pr->flags &= ~BLKID_FL_TINY_DEV;

	if (pr->size <= 1440 * 1024 && !S_ISCHR(pr->mode))
		pr->flags |= BLKID_FL_TINY_DEV;

	blkid_probe_reset_buffer(pr);

	return 0;
}
