posix_clock_fasync(int fd, struct file *fp, int on)
{
	struct posix_clock *clk = get_posix_clock(fp);
	int err = 0;

	if (!clk)
		return -ENODEV;

	if (clk->ops.fasync)
		err = clk->ops.fasync(clk, fd, fp, on);

	put_posix_clock(clk);

	return err;
}
