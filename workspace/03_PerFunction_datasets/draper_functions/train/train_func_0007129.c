docg4_wait(struct mtd_info *mtd, struct nand_chip *nand)
{

	struct docg4_priv *doc = nand->priv;
	int status = NAND_STATUS_WP;
	dev_dbg(doc->dev, "%s...\n", __func__);


	if (doc->status) {
		status |= doc->status;
		doc->status = 0;
		return status;
	}

	status |= poll_status(doc);
	return status;
}
