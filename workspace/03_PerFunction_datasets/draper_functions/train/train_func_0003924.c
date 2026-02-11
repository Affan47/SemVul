pm_clk_add_notifier(struct bus_type *bus,
				 struct pm_clk_notifier_block *clknb)
{
	if (!bus || !clknb)
		return;

	clknb->nb.notifier_call = pm_clk_notify;
	bus_register_notifier(bus, &clknb->nb);
}
