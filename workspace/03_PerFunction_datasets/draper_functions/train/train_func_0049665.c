clk_requires_trigger(struct kona_clk *bcm_clk)
{
	struct peri_clk_data *peri = bcm_clk->u.peri;
	struct bcm_clk_sel *sel;
	struct bcm_clk_div *div;

	if (bcm_clk->type != bcm_clk_peri)
		return false;

	sel = &peri->sel;
	if (sel->parent_count && selector_exists(sel))
		return true;

	div = &peri->div;
	if (!divider_exists(div))
		return false;


	if (!divider_is_fixed(div))
		return true;

	div = &peri->pre_div;

	return divider_exists(div) && !divider_is_fixed(div);
}
