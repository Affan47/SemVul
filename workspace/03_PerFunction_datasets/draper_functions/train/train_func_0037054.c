clk_composite_determine_rate(struct clk_hw *hw,
					struct clk_rate_request *req)
{
	struct clk_composite *composite = to_clk_composite(hw);
	const struct clk_ops *rate_ops = composite->rate_ops;
	const struct clk_ops *mux_ops = composite->mux_ops;
	struct clk_hw *rate_hw = composite->rate_hw;
	struct clk_hw *mux_hw = composite->mux_hw;
	struct clk_hw *parent;
	unsigned long parent_rate;
	long tmp_rate, best_rate = 0;
	unsigned long rate_diff;
	unsigned long best_rate_diff = ULONG_MAX;
	long rate;
	int i;

	if (rate_hw && rate_ops && rate_ops->determine_rate) {
		__clk_hw_set_clk(rate_hw, hw);
		return rate_ops->determine_rate(rate_hw, req);
	} else if (rate_hw && rate_ops && rate_ops->round_rate &&
		   mux_hw && mux_ops && mux_ops->set_parent) {
		req->best_parent_hw = NULL;

		if (clk_hw_get_flags(hw) & CLK_SET_RATE_NO_REPARENT) {
			parent = clk_hw_get_parent(mux_hw);
			req->best_parent_hw = parent;
			req->best_parent_rate = clk_hw_get_rate(parent);

			rate = rate_ops->round_rate(rate_hw, req->rate,
						    &req->best_parent_rate);
			if (rate < 0)
				return rate;

			req->rate = rate;
			return 0;
		}

		for (i = 0; i < clk_hw_get_num_parents(mux_hw); i++) {
			parent = clk_hw_get_parent_by_index(mux_hw, i);
			if (!parent)
				continue;

			parent_rate = clk_hw_get_rate(parent);

			tmp_rate = rate_ops->round_rate(rate_hw, req->rate,
							&parent_rate);
			if (tmp_rate < 0)
				continue;

			rate_diff = abs(req->rate - tmp_rate);

			if (!rate_diff || !req->best_parent_hw
				       || best_rate_diff > rate_diff) {
				req->best_parent_hw = parent;
				req->best_parent_rate = parent_rate;
				best_rate_diff = rate_diff;
				best_rate = tmp_rate;
			}

			if (!rate_diff)
				return 0;
		}

		req->rate = best_rate;
		return 0;
	} else if (mux_hw && mux_ops && mux_ops->determine_rate) {
		__clk_hw_set_clk(mux_hw, hw);
		return mux_ops->determine_rate(mux_hw, req);
	} else {
		pr_err("clk: clk_composite_determine_rate function called, but no mux or rate callback set!\n");
		return -EINVAL;
	}
}
