nand_update_bbt(struct mtd_info *mtd, loff_t offs)
{
	struct nand_chip *this = mtd->priv;
	int len, res = 0;
	int chip, chipsel;
	uint8_t *buf;
	struct nand_bbt_descr *td = this->bbt_td;
	struct nand_bbt_descr *md = this->bbt_md;

	if (!this->bbt || !td)
		return -EINVAL;


	len = (1 << this->bbt_erase_shift);
	len += (len >> this->page_shift) * mtd->oobsize;
	buf = kmalloc(len, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;


	if (td->options & NAND_BBT_PERCHIP) {
		chip = (int)(offs >> this->chip_shift);
		chipsel = chip;
	} else {
		chip = 0;
		chipsel = -1;
	}

	td->version[chip]++;
	if (md)
		md->version[chip]++;


	if (td->options & NAND_BBT_WRITE) {
		res = write_bbt(mtd, buf, td, md, chipsel);
		if (res < 0)
			goto out;
	}

	if (md && (md->options & NAND_BBT_WRITE)) {
		res = write_bbt(mtd, buf, md, td, chipsel);
	}

 out:
	kfree(buf);
	return res;
}
