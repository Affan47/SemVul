clk_pixel_determine_rate(struct clk_hw *hw,
				    struct clk_rate_request *req)
{
	unsigned long request, src_rate;
	int delta = 100000;
	const struct frac_entry *frac = frac_table_pixel;

	for (; frac->num; frac++) {
		request = (req->rate * frac->den) / frac->num;

		src_rate = clk_hw_round_rate(req->best_parent_hw, request);
		if ((src_rate < (request - delta)) ||
			(src_rate > (request + delta)))
			continue;

		req->best_parent_rate = src_rate;
		req->rate = (src_rate * frac->num) / frac->den;
		return 0;
	}

	return -EINVAL;
}
