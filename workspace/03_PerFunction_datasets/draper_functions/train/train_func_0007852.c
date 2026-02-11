jffs2_write_nand_cleanmarker(struct jffs2_sb_info *c,
				 struct jffs2_eraseblock *jeb)
{
	int ret;
	struct mtd_oob_ops ops;
	int cmlen = min_t(int, c->oobavail, OOB_CM_SIZE);

	ops.mode = MTD_OPS_AUTO_OOB;
	ops.ooblen = cmlen;
	ops.oobbuf = (uint8_t *)&oob_cleanmarker;
	ops.len = ops.ooboffs = ops.retlen = ops.oobretlen = 0;
	ops.datbuf = NULL;

	ret = mtd_write_oob(c->mtd, jeb->offset, &ops);
	if (ret || ops.oobretlen != ops.ooblen) {
		pr_err("cannot write OOB for EB at %08x, requested %zd bytes, read %zd bytes, error %d\n",
		       jeb->offset, ops.ooblen, ops.oobretlen, ret);
		if (!ret)
			ret = -EIO;
		return ret;
	}

	return 0;
}
