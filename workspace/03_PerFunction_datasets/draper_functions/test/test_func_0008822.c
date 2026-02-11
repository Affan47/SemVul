v4l2_clk_get_rate(struct v4l2_clk *clk)
{
	int ret;

	if (clk->clk)
		return clk_get_rate(clk->clk);

	ret = v4l2_clk_lock_driver(clk);
	if (ret < 0)
		return ret;

	mutex_lock(&clk->lock);
	if (!clk->ops->get_rate)
		ret = -ENOSYS;
	else
		ret = clk->ops->get_rate(clk);
	mutex_unlock(&clk->lock);

	v4l2_clk_unlock_driver(clk);

	return ret;
}
