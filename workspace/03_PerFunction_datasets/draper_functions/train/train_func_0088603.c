clk_fd_set_rate(struct clk_hw *hw, unsigned long rate,
			   unsigned long parent_rate)
{
	struct clk_fractional_divider *fd = to_clk_fd(hw);
	unsigned long flags = 0;
	unsigned long m, n;
	u32 val;

	rational_best_approximation(rate, parent_rate,
			GENMASK(fd->mwidth - 1, 0), GENMASK(fd->nwidth - 1, 0),
			&m, &n);

	if (fd->lock)
		spin_lock_irqsave(fd->lock, flags);
	else
		__acquire(fd->lock);

	val = clk_readl(fd->reg);
	val &= ~(fd->mmask | fd->nmask);
	val |= (m << fd->mshift) | (n << fd->nshift);
	clk_writel(val, fd->reg);

	if (fd->lock)
		spin_unlock_irqrestore(fd->lock, flags);
	else
		__release(fd->lock);

	return 0;
}
