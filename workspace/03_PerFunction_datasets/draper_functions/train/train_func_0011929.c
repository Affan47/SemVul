udf_load_vrs(struct super_block *sb, struct udf_options *uopt,
			int silent, struct kernel_lb_addr *fileset)
{
	struct udf_sb_info *sbi = UDF_SB(sb);
	loff_t nsr_off;
	int ret;

	if (!sb_set_blocksize(sb, uopt->blocksize)) {
		if (!silent)
			udf_warn(sb, "Bad block size\n");
		return -EINVAL;
	}
	sbi->s_last_block = uopt->lastblock;
	if (!uopt->novrs) {

		nsr_off = udf_check_vsd(sb);
		if (!nsr_off) {
			if (!silent)
				udf_warn(sb, "No VRS found\n");
			return 0;
		}
		if (nsr_off == -1)
			udf_debug("Failed to read sector at offset %d. "
				  "Assuming open disc. Skipping validity "
				  "check\n", VSD_FIRST_SECTOR_OFFSET);
		if (!sbi->s_last_block)
			sbi->s_last_block = udf_get_last_block(sb);
	} else {
		udf_debug("Validity check skipped because of novrs option\n");
	}


	sbi->s_anchor = uopt->anchor;
	ret = udf_find_anchor(sb, fileset);
	if (ret < 0) {
		if (!silent && ret == -EAGAIN)
			udf_warn(sb, "No anchor found\n");
		return ret;
	}
	return 0;
}
