find_media_headers(struct mtd_info *mtd, u_char *buf, const char *id, int findmirror)
{
	struct nand_chip *this = mtd->priv;
	struct doc_priv *doc = this->priv;
	unsigned offs;
	int ret;
	size_t retlen;

	for (offs = 0; offs < mtd->size; offs += mtd->erasesize) {
		ret = mtd_read(mtd, offs, mtd->writesize, &retlen, buf);
		if (retlen != mtd->writesize)
			continue;
		if (ret) {
			printk(KERN_WARNING "ECC error scanning DOC at 0x%x\n", offs);
		}
		if (memcmp(buf, id, 6))
			continue;
		printk(KERN_INFO "Found DiskOnChip %s Media Header at 0x%x\n", id, offs);
		if (doc->mh0_page == -1) {
			doc->mh0_page = offs >> this->page_shift;
			if (!findmirror)
				return 1;
			continue;
		}
		doc->mh1_page = offs >> this->page_shift;
		return 2;
	}
	if (doc->mh0_page == -1) {
		printk(KERN_WARNING "DiskOnChip %s Media Header not found.\n", id);
		return 0;
	}


	offs = doc->mh0_page << this->page_shift;
	ret = mtd_read(mtd, offs, mtd->writesize, &retlen, buf);
	if (retlen != mtd->writesize) {

		printk(KERN_ERR "Read DiskOnChip Media Header once, but can't reread it???\n");
		return 0;
	}
	return 1;
}
