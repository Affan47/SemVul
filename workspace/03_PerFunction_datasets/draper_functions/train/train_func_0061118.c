part_read_oob(struct mtd_info *mtd, loff_t from,
		struct mtd_oob_ops *ops)
{
	struct mtd_part *part = PART(mtd);
	int res;

	if (from >= mtd->size)
		return -EINVAL;
	if (ops->datbuf && from + ops->len > mtd->size)
		return -EINVAL;


	if (ops->oobbuf) {
		size_t len, pages;

		if (ops->mode == MTD_OPS_AUTO_OOB)
			len = mtd->oobavail;
		else
			len = mtd->oobsize;
		pages = mtd_div_by_ws(mtd->size, mtd);
		pages -= mtd_div_by_ws(from, mtd);
		if (ops->ooboffs + ops->ooblen > pages * len)
			return -EINVAL;
	}

	res = part->master->_read_oob(part->master, from + part->offset, ops);
	if (unlikely(res)) {
		if (mtd_is_bitflip(res))
			mtd->ecc_stats.corrected++;
		if (mtd_is_eccerr(res))
			mtd->ecc_stats.failed++;
	}
	return res;
}
