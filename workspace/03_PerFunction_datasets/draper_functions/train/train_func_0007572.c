pc_clock_adjtime(clockid_t id, struct timex *tx)
{
	struct posix_clock_desc cd;
	int err;

	err = get_clock_desc(id, &cd);
	if (err)
		return err;

	if ((cd.fp->f_mode & FMODE_WRITE) == 0) {
		err = -EACCES;
		goto out;
	}

	if (cd.clk->ops.clock_adjtime)
		err = cd.clk->ops.clock_adjtime(cd.clk, tx);
	else
		err = -EOPNOTSUPP;
out:
	put_clock_desc(&cd);

	return err;
}
