blkid_probe_get_sectorsize(blkid_probe pr)
{
	if (!pr)
		return DEFAULT_SECTOR_SIZE;

	if (pr->blkssz)
		return pr->blkssz;

	if (S_ISBLK(pr->mode) &&
	    blkdev_get_sector_size(pr->fd, (int *) &pr->blkssz) == 0)
		return pr->blkssz;

	pr->blkssz = DEFAULT_SECTOR_SIZE;
	return pr->blkssz;
}
