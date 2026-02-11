otp_select_filemode(struct mtd_file_info *mfi, int mode)
{
	struct mtd_info *mtd = mfi->mtd;
	size_t retlen;

	switch (mode) {
	case MTD_OTP_FACTORY:
		if (mtd_read_fact_prot_reg(mtd, -1, 0, &retlen, NULL) ==
				-EOPNOTSUPP)
			return -EOPNOTSUPP;

		mfi->mode = MTD_FILE_MODE_OTP_FACTORY;
		break;
	case MTD_OTP_USER:
		if (mtd_read_user_prot_reg(mtd, -1, 0, &retlen, NULL) ==
				-EOPNOTSUPP)
			return -EOPNOTSUPP;

		mfi->mode = MTD_FILE_MODE_OTP_USER;
		break;
	case MTD_OTP_OFF:
		mfi->mode = MTD_FILE_MODE_NORMAL;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
