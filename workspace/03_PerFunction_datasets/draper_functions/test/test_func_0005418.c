onenand_mlc_read_ops_nolock(struct mtd_info *mtd, loff_t from,
				struct mtd_oob_ops *ops)
{
	struct onenand_chip *this = mtd->priv;
	struct mtd_ecc_stats stats;
	size_t len = ops->len;
	size_t ooblen = ops->ooblen;
	u_char *buf = ops->datbuf;
	u_char *oobbuf = ops->oobbuf;
	int read = 0, column, thislen;
	int oobread = 0, oobcolumn, thisooblen, oobsize;
	int ret = 0;
	int writesize = this->writesize;

	pr_debug("%s: from = 0x%08x, len = %i\n", __func__, (unsigned int)from,
			(int)len);

	if (ops->mode == MTD_OPS_AUTO_OOB)
		oobsize = this->ecclayout->oobavail;
	else
		oobsize = mtd->oobsize;

	oobcolumn = from & (mtd->oobsize - 1);


	if (from + len > mtd->size) {
		printk(KERN_ERR "%s: Attempt read beyond end of device\n",
			__func__);
		ops->retlen = 0;
		ops->oobretlen = 0;
		return -EINVAL;
	}

	stats = mtd->ecc_stats;

	while (read < len) {
		cond_resched();

		thislen = min_t(int, writesize, len - read);

		column = from & (writesize - 1);
		if (column + thislen > writesize)
			thislen = writesize - column;

		if (!onenand_check_bufferram(mtd, from)) {
			this->command(mtd, ONENAND_CMD_READ, from, writesize);

			ret = this->wait(mtd, FL_READING);
			if (unlikely(ret))
				ret = onenand_recover_lsb(mtd, from, ret);
			onenand_update_bufferram(mtd, from, !ret);
			if (mtd_is_eccerr(ret))
				ret = 0;
			if (ret)
				break;
		}

		this->read_bufferram(mtd, ONENAND_DATARAM, buf, column, thislen);
		if (oobbuf) {
			thisooblen = oobsize - oobcolumn;
			thisooblen = min_t(int, thisooblen, ooblen - oobread);

			if (ops->mode == MTD_OPS_AUTO_OOB)
				onenand_transfer_auto_oob(mtd, oobbuf, oobcolumn, thisooblen);
			else
				this->read_bufferram(mtd, ONENAND_SPARERAM, oobbuf, oobcolumn, thisooblen);
			oobread += thisooblen;
			oobbuf += thisooblen;
			oobcolumn = 0;
		}

		read += thislen;
		if (read == len)
			break;

		from += thislen;
		buf += thislen;
	}


	ops->retlen = read;
	ops->oobretlen = oobread;

	if (ret)
		return ret;

	if (mtd->ecc_stats.failed - stats.failed)
		return -EBADMSG;


	return mtd->ecc_stats.corrected != stats.corrected ? 1 : 0;
}
