mtd_write_user_prot_reg(struct mtd_info *mtd, loff_t to, size_t len,
			    size_t *retlen, u_char *buf)
{
	int ret;

	*retlen = 0;
	if (!mtd->_write_user_prot_reg)
		return -EOPNOTSUPP;
	if (!len)
		return 0;
	ret = mtd->_write_user_prot_reg(mtd, to, len, retlen, buf);
	if (ret)
		return ret;


	return (*retlen) ? 0 : -ENOSPC;
}
