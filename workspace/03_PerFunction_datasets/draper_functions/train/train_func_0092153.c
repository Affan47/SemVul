kona_ccu_teardown(struct ccu_data *ccu)
{
	kfree(ccu->clk_data.clks);
	ccu->clk_data.clks = NULL;
	if (!ccu->base)
		return;

	of_clk_del_provider(ccu->node);
	ccu_clks_teardown(ccu);
	of_node_put(ccu->node);
	ccu->node = NULL;
	iounmap(ccu->base);
	ccu->base = NULL;
}
