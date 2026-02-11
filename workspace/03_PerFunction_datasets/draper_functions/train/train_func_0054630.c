clk_set_rate_range(struct clk *clk, unsigned long min, unsigned long max)
{
	int ret = 0;

	if (!clk)
		return 0;

	if (min > max) {
		pr_err("%s: clk %s dev %s con %s: invalid range [%lu, %lu]\n",
		       __func__, clk->core->name, clk->dev_id, clk->con_id,
		       min, max);
		return -EINVAL;
	}

	clk_prepare_lock();

	if (min != clk->min_rate || max != clk->max_rate) {
		clk->min_rate = min;
		clk->max_rate = max;
		ret = clk_core_set_rate_nolock(clk->core, clk->core->req_rate);
	}

	clk_prepare_unlock();

	return ret;
}
