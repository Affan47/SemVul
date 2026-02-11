clk_core_round_rate_nolock(struct clk_core *core,
				      struct clk_rate_request *req)
{
	struct clk_core *parent;
	long rate;

	lockdep_assert_held(&prepare_lock);

	if (!core)
		return 0;

	parent = core->parent;
	if (parent) {
		req->best_parent_hw = parent->hw;
		req->best_parent_rate = parent->rate;
	} else {
		req->best_parent_hw = NULL;
		req->best_parent_rate = 0;
	}

	if (core->ops->determine_rate) {
		return core->ops->determine_rate(core->hw, req);
	} else if (core->ops->round_rate) {
		rate = core->ops->round_rate(core->hw, req->rate,
					     &req->best_parent_rate);
		if (rate < 0)
			return rate;

		req->rate = rate;
	} else if (core->flags & CLK_SET_RATE_PARENT) {
		return clk_core_round_rate_nolock(parent, req);
	} else {
		req->rate = core->rate;
	}

	return 0;
}
