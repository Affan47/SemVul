onenand_otp_walk(struct mtd_info *mtd, loff_t from, size_t len,
			size_t *retlen, u_char *buf,
			otp_op_t action, int mode)
{
	struct onenand_chip *this = mtd->priv;
	int otp_pages;
	int density;
	int ret = 0;

	*retlen = 0;

	density = onenand_get_density(this->device_id);
	if (density < ONENAND_DEVICE_DENSITY_512Mb)
		otp_pages = 20;
	else
		otp_pages = 50;

	if (mode == MTD_OTP_FACTORY) {
		from += mtd->writesize * otp_pages;
		otp_pages = ONENAND_PAGES_PER_BLOCK - otp_pages;
	}


	if (mode == MTD_OTP_USER) {
		if (mtd->writesize * otp_pages < from + len)
			return 0;
	} else {
		if (mtd->writesize * otp_pages <  len)
			return 0;
	}

	onenand_get_device(mtd, FL_OTPING);
	while (len > 0 && otp_pages > 0) {
		if (!action) {
			struct otp_info *otpinfo;

			len -= sizeof(struct otp_info);
			if (len <= 0) {
				ret = -ENOSPC;
				break;
			}

			otpinfo = (struct otp_info *) buf;
			otpinfo->start = from;
			otpinfo->length = mtd->writesize;
			otpinfo->locked = 0;

			from += mtd->writesize;
			buf += sizeof(struct otp_info);
			*retlen += sizeof(struct otp_info);
		} else {
			size_t tmp_retlen;

			ret = action(mtd, from, len, &tmp_retlen, buf);

			buf += tmp_retlen;
			len -= tmp_retlen;
			*retlen += tmp_retlen;

			if (ret)
				break;
		}
		otp_pages--;
	}
	onenand_release_device(mtd);

	return ret;
}
