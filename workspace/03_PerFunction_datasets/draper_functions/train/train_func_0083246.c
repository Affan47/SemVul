dlm_nodir_store(struct dlm_ls *ls, const char *buf, size_t len)
{
	int val;
	int rc = kstrtoint(buf, 0, &val);

	if (rc)
		return rc;
	if (val == 1)
		set_bit(LSFL_NODIR, &ls->ls_flags);
	return len;
}
