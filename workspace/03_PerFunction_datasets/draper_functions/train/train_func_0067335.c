get_fold_mark(struct NFTLrecord *nftl, unsigned int block)
{
	struct mtd_info *mtd = nftl->mbd.mtd;
	struct nftl_uci2 uci;
	size_t retlen;

	if (nftl_read_oob(mtd, block * nftl->EraseSize + 2 * SECTORSIZE + 8,
			  8, &retlen, (char *)&uci) < 0)
		return 0;

	return le16_to_cpu((uci.FoldMark | uci.FoldMark1));
}
