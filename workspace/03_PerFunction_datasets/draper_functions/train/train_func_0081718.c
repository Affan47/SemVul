gf_sc_next_frame_state(GF_Compositor *compositor, u32 state)
{
	GF_LOG(GF_LOG_DEBUG, GF_LOG_COMPOSE, ("[Compositor] Forcing frame redraw state: %d\n", state));
	compositor->frame_draw_type = state;
	if (state==GF_SC_DRAW_FLUSH)
		compositor->skip_flush = 2;
}
