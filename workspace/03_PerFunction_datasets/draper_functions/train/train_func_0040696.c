mtdswap_gc(struct mtdswap_dev *d, unsigned int background)
{
	struct swap_eb *eb;
	int ret;

	if (d->spare_eblks < MIN_SPARE_EBLOCKS)
		return 1;

	eb = mtdswap_pick_gc_eblk(d, background);
	if (!eb)
		return 1;

	ret = mtdswap_gc_eblock(d, eb);
	if (ret == -ENOSPC)
		return 1;

	if (eb->flags & EBLOCK_FAILED) {
		mtdswap_handle_badblock(d, eb);
		return 0;
	}

	eb->flags &= ~EBLOCK_BITFLIP;
	ret = mtdswap_erase_block(d, eb);
	if ((eb->flags & EBLOCK_READERR) &&
		(ret || !mtdswap_eblk_passes(d, eb)))
		return 0;

	if (ret == 0)
		ret = mtdswap_write_marker(d, eb, MTDSWAP_TYPE_CLEAN);

	if (ret == 0)
		mtdswap_rb_add(d, eb, MTDSWAP_CLEAN);
	else if (ret != -EIO && !mtd_is_eccerr(ret))
		mtdswap_rb_add(d, eb, MTDSWAP_DIRTY);

	return 0;
}
