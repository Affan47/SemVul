read_physical_sector(struct mtd_info *mtd, uint8_t *sect_buf,
				int sect_no)
{
	int ret;
	size_t retlen;
	loff_t offset = (loff_t)sect_no << SECTOR_SHIFT;

	ret = mtd_read(mtd, offset, SECTOR_SIZE, &retlen, sect_buf);
	if (ret < 0 || retlen != SECTOR_SIZE)
		return -1;

	return 0;
}
