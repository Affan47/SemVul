rv6xx_generate_steps(struct radeon_device *rdev,
				 u32 low, u32 high,
                                 u32 start_index, u8 *end_index)
{
	struct rv6xx_sclk_stepping cur;
	struct rv6xx_sclk_stepping target;
	bool increasing_vco;
	u32 step_index = start_index;

	rv6xx_convert_clock_to_stepping(rdev, low, &cur);
	rv6xx_convert_clock_to_stepping(rdev, high, &target);

	rv6xx_output_stepping(rdev, step_index++, &cur);

	increasing_vco = (target.vco_frequency >= cur.vco_frequency);

	if (target.post_divider > cur.post_divider)
		cur.post_divider = target.post_divider;

	while (1) {
		struct rv6xx_sclk_stepping next;

		if (rv6xx_can_step_post_div(rdev, &cur, &target))
			next = rv6xx_next_post_div_step(rdev, &cur, &target);
		else
			next = rv6xx_next_vco_step(rdev, &cur, increasing_vco, R600_VCOSTEPPCT_DFLT);

		if (rv6xx_reached_stepping_target(rdev, &next, &target, increasing_vco)) {
			struct rv6xx_sclk_stepping tiny =
				rv6xx_next_vco_step(rdev, &target, !increasing_vco, R600_ENDINGVCOSTEPPCT_DFLT);
			tiny.post_divider = next.post_divider;

			if (!rv6xx_reached_stepping_target(rdev, &tiny, &cur, !increasing_vco))
				rv6xx_output_stepping(rdev, step_index++, &tiny);

			if ((next.post_divider != target.post_divider) &&
			    (next.vco_frequency != target.vco_frequency)) {
				struct rv6xx_sclk_stepping final_vco;

				final_vco.vco_frequency = target.vco_frequency;
				final_vco.post_divider = next.post_divider;

				rv6xx_output_stepping(rdev, step_index++, &final_vco);
			}

			rv6xx_output_stepping(rdev, step_index++, &target);
			break;
		} else
			rv6xx_output_stepping(rdev, step_index++, &next);

		cur = next;
	}

	*end_index = (u8)step_index - 1;

}
