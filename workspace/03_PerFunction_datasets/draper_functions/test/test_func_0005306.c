goldfish_nand_write_oob(struct mtd_info *mtd, loff_t ofs,
				   struct mtd_oob_ops *ops)
{
	u32 rem;

	if (ofs + ops->len > mtd->size)
		goto invalid_arg;
	if (ops->len && ops->len != mtd->writesize)
		goto invalid_arg;
	if (ops->ooblen + ops->ooboffs > mtd->oobsize)
		goto invalid_arg;

	rem = do_div(ofs, mtd->writesize);
	if (rem)
		goto invalid_arg;
	ofs *= (mtd->writesize + mtd->oobsize);

	if (ops->datbuf)
		ops->retlen = goldfish_nand_cmd(mtd, NAND_CMD_WRITE, ofs,
						ops->len, ops->datbuf);
	ofs += mtd->writesize + ops->ooboffs;
	if (ops->oobbuf)
		ops->oobretlen = goldfish_nand_cmd(mtd, NAND_CMD_WRITE, ofs,
						ops->ooblen, ops->oobbuf);
	return 0;

invalid_arg:
	pr_err("goldfish_nand_write_oob: invalid write, start %llx, len %zx, ooblen %zx, dev_size %llx, write_size %x\n",
	       ofs, ops->len, ops->ooblen, mtd->size, mtd->writesize);
	return -EINVAL;
}
