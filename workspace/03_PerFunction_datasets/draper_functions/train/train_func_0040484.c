onenand_isbad_bbt(struct mtd_info *mtd, loff_t offs, int allowbbt)
{
	struct onenand_chip *this = mtd->priv;
	struct bbm_info *bbm = this->bbm;
	int block;
	uint8_t res;


	block = (int) (onenand_block(this, offs) << 1);
	res = (bbm->bbt[block >> 3] >> (block & 0x06)) & 0x03;

	pr_debug("onenand_isbad_bbt: bbt info for offs 0x%08x: (block %d) 0x%02x\n",
		(unsigned int) offs, block >> 1, res);

	switch ((int) res) {
	case 0x00:	return 0;
	case 0x01:	return 1;
	case 0x02:	return allowbbt ? 0 : 1;
	}

	return 1;
}
