clk_unprepare(struct clk *clk)
{
	if (IS_ERR_OR_NULL(clk))
		return;

	clk_prepare_lock();
	clk_core_unprepare(clk->core);
	clk_prepare_unlock();
}
