nand_do_write_oob(struct mtd_info *mtd, loff_t to,
			     struct mtd_oob_ops *ops)
{
	int chipnr, page, status, len;
	struct nand_chip *chip = mtd->priv;

	pr_debug("%s: to = 0x%08x, len = %i\n",
			 __func__, (unsigned int)to, (int)ops->ooblen);

	if (ops->mode == MTD_OPS_AUTO_OOB)
		len = chip->ecc.layout->oobavail;
	else
		len = mtd->oobsize;


	if ((ops->ooboffs + ops->ooblen) > len) {
		pr_debug("%s: attempt to write past end of page\n",
				__func__);
		return -EINVAL;
	}

	if (unlikely(ops->ooboffs >= len)) {
		pr_debug("%s: attempt to start write outside oob\n",
				__func__);
		return -EINVAL;
	}


	if (unlikely(to >= mtd->size ||
		     ops->ooboffs + ops->ooblen >
			((mtd->size >> chip->page_shift) -
			 (to >> chip->page_shift)) * len)) {
		pr_debug("%s: attempt to write beyond end of device\n",
				__func__);
		return -EINVAL;
	}

	chipnr = (int)(to >> chip->chip_shift);
	chip->select_chip(mtd, chipnr);


	page = (int)(to >> chip->page_shift);


	chip->cmdfunc(mtd, NAND_CMD_RESET, -1, -1);


	if (nand_check_wp(mtd)) {
		chip->select_chip(mtd, -1);
		return -EROFS;
	}


	if (page == chip->pagebuf)
		chip->pagebuf = -1;

	nand_fill_oob(mtd, ops->oobbuf, ops->ooblen, ops);

	if (ops->mode == MTD_OPS_RAW)
		status = chip->ecc.write_oob_raw(mtd, chip, page & chip->pagemask);
	else
		status = chip->ecc.write_oob(mtd, chip, page & chip->pagemask);

	chip->select_chip(mtd, -1);

	if (status)
		return status;

	ops->oobretlen = ops->ooblen;

	return 0;
}
