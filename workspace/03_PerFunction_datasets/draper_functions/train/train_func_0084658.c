gf_term_set_simulation_frame_rate(GF_Terminal * term, Double frame_rate)
{
	if (!term) return GF_BAD_PARAM;
	term->frame_duration = (u32) (1000.0 / frame_rate);
	gf_sc_set_fps(term->compositor, frame_rate);
	return GF_OK;
}
