ns_nand_read_word(struct mtd_info *mtd)
{
	struct nand_chip *chip = (struct nand_chip *)mtd->priv;

	NS_DBG("read_word\n");

	return chip->read_byte(mtd) | (chip->read_byte(mtd) << 8);
}
