__set_clk_rates(struct device_node *node, bool clk_supplier)
{
	struct of_phandle_args clkspec;
	struct property	*prop;
	const __be32 *cur;
	int rc, index = 0;
	struct clk *clk;
	u32 rate;

	of_property_for_each_u32(node, "assigned-clock-rates", prop, cur, rate) {
		if (rate) {
			rc = of_parse_phandle_with_args(node, "assigned-clocks",
					"#clock-cells",	index, &clkspec);
			if (rc < 0) {

				if (rc == -ENOENT)
					continue;
				else
					return rc;
			}
			if (clkspec.np == node && !clk_supplier)
				return 0;

			clk = of_clk_get_from_provider(&clkspec);
			if (IS_ERR(clk)) {
				pr_warn("clk: couldn't get clock %d for %s\n",
					index, node->full_name);
				return PTR_ERR(clk);
			}

			rc = clk_set_rate(clk, rate);
			if (rc < 0)
				pr_err("clk: couldn't set %s clk rate to %d (%d), current rate: %ld\n",
				       __clk_get_name(clk), rate, rc,
				       clk_get_rate(clk));
			clk_put(clk);
		}
		index++;
	}
	return 0;
}
