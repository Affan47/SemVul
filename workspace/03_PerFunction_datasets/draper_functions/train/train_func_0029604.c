clk_core_get_rate(struct clk_core *core)
{
	unsigned long rate;

	clk_prepare_lock();

	if (core && (core->flags & CLK_GET_RATE_NOCACHE))
		__clk_recalc_rates(core, 0);

	rate = clk_core_get_rate_nolock(core);
	clk_prepare_unlock();

	return rate;
}
