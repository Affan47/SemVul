initbmap(FILE *dev_ptr, int64_t nblocks)
{
	int level, rc = 0;
	int64_t next_page;


	level = BMAPSZTOLEV(nblocks);
	next_page = BMAP_OFF + PSIZE + PSIZE * (2 - level);


	rc = initctl(dev_ptr, 0, nblocks, level, &control_page->dn_maxfreebud,
		     &next_page);
	if (rc != 0)
		return (rc);


	ujfs_swap_dbmap(control_page);
	rc = ujfs_rw_diskblocks(dev_ptr, BMAP_OFF, PSIZE, control_page, PUT);
	ujfs_swap_dbmap(control_page);

	return (rc);
}
