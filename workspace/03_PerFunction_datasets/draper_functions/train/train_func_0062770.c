read_abs_bbts(struct mtd_info *mtd, uint8_t *buf,
			  struct nand_bbt_descr *td, struct nand_bbt_descr *md)
{
	struct nand_chip *this = mtd->priv;


	if (td->options & NAND_BBT_VERSION) {
		scan_read(mtd, buf, (loff_t)td->pages[0] << this->page_shift,
			      mtd->writesize, td);
		td->version[0] = buf[bbt_get_ver_offs(mtd, td)];
		pr_info("Bad block table at page %d, version 0x%02X\n",
			 td->pages[0], td->version[0]);
	}


	if (md && (md->options & NAND_BBT_VERSION)) {
		scan_read(mtd, buf, (loff_t)md->pages[0] << this->page_shift,
			      mtd->writesize, md);
		md->version[0] = buf[bbt_get_ver_offs(mtd, md)];
		pr_info("Bad block table at page %d, version 0x%02X\n",
			 md->pages[0], md->version[0]);
	}
}
