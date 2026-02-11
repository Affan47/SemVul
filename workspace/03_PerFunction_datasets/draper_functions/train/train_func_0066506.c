xgene_clk_set_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long parent_rate)
{
	struct xgene_clk *pclk = to_xgene_clk(hw);
	unsigned long flags = 0;
	u32 data;
	u32 divider;
	u32 divider_save;

	if (pclk->lock)
		spin_lock_irqsave(pclk->lock, flags);

	if (pclk->param.divider_reg) {

		if (rate > parent_rate)
			rate = parent_rate;
		divider_save = divider = parent_rate / rate;
		divider &= (1 << pclk->param.reg_divider_width) - 1;
		divider <<= pclk->param.reg_divider_shift;


		data = xgene_clk_read(pclk->param.divider_reg +
				pclk->param.reg_divider_offset);
		data &= ~(((1 << pclk->param.reg_divider_width) - 1)
				<< pclk->param.reg_divider_shift);
		data |= divider;
		xgene_clk_write(data, pclk->param.divider_reg +
					pclk->param.reg_divider_offset);
		pr_debug("%s clock set rate %ld\n", clk_hw_get_name(hw),
			parent_rate / divider_save);
	} else {
		divider_save = 1;
	}

	if (pclk->lock)
		spin_unlock_irqrestore(pclk->lock, flags);

	return parent_rate / divider_save;
}
