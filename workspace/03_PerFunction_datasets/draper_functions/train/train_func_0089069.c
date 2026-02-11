gf_sc_draw_frame(GF_Compositor *compositor)
{
	gf_sc_simulation_tick(compositor);
	if (compositor->frame_draw_type) return 1;
	if (compositor->fonts_pending) return 1;
	return 0;
}
