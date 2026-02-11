spinand_read_page_hwecc(struct mtd_info *mtd, struct nand_chip *chip,
				   u8 *buf, int oob_required, int page)
{
	int retval;
	u8 status;
	u8 *p = buf;
	int eccsize = chip->ecc.size;
	int eccsteps = chip->ecc.steps;
	struct spinand_info *info = (struct spinand_info *)chip->priv;

	enable_read_hw_ecc = 1;

	chip->read_buf(mtd, p, eccsize * eccsteps);
	if (oob_required)
		chip->read_buf(mtd, chip->oob_poi, mtd->oobsize);

	while (1) {
		retval = spinand_read_status(info->spi, &status);
		if (retval < 0) {
			dev_err(&mtd->dev,
				"error %d reading status register\n", retval);
			return retval;
		}

		if ((status & STATUS_OIP_MASK) == STATUS_READY) {
			if ((status & STATUS_ECC_MASK) == STATUS_ECC_ERROR) {
				pr_info("spinand: ECC error\n");
				mtd->ecc_stats.failed++;
			} else if ((status & STATUS_ECC_MASK) ==
					STATUS_ECC_1BIT_CORRECTED)
				mtd->ecc_stats.corrected++;
			break;
		}
	}
	return 0;
}
