nand_block_markbad_lowlevel(struct mtd_info *mtd, loff_t ofs)
{
	struct nand_chip *chip = mtd->priv;
	int res, ret = 0;

	if (!(chip->bbt_options & NAND_BBT_NO_OOB_BBM)) {
		struct erase_info einfo;


		memset(&einfo, 0, sizeof(einfo));
		einfo.mtd = mtd;
		einfo.addr = ofs;
		einfo.len = 1ULL << chip->phys_erase_shift;
		nand_erase_nand(mtd, &einfo, 0);


		nand_get_device(mtd, FL_WRITING);
		ret = chip->block_markbad(mtd, ofs);
		nand_release_device(mtd);
	}


	if (chip->bbt) {
		res = nand_markbad_bbt(mtd, ofs);
		if (!ret)
			ret = res;
	}

	if (!ret)
		mtd->ecc_stats.badblocks++;

	return ret;
}
