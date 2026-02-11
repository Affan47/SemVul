nand_isbad_bbt(struct mtd_info *mtd, loff_t offs, int allowbbt)
{
	struct nand_chip *this = mtd->priv;
	int block, res;

	block = (int)(offs >> this->bbt_erase_shift);
	res = bbt_get_entry(this, block);

	pr_debug("nand_isbad_bbt(): bbt info for offs 0x%08x: (block %d) 0x%02x\n",
		 (unsigned int)offs, block, res);

	switch (res) {
	case BBT_BLOCK_GOOD:
		return 0;
	case BBT_BLOCK_WORN:
		return 1;
	case BBT_BLOCK_RESERVED:
		return allowbbt ? 0 : 1;
	}
	return 1;
}
