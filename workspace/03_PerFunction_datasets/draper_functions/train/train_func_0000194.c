doc2000_read_byte(struct mtd_info *mtd)
{
	struct nand_chip *this = mtd->priv;
	struct doc_priv *doc = this->priv;
	void __iomem *docptr = doc->virtadr;
	u_char ret;

	ReadDOC(docptr, CDSNSlowIO);
	DoC_Delay(doc, 2);
	ret = ReadDOC(docptr, 2k_CDSN_IO);
	if (debug)
		printk("read_byte returns %02x\n", ret);
	return ret;
}
