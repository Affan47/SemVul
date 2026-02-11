kHaveMouse(state_t *s, int funct_nr, int argc, reg_t *argv)
{

	return make_reg (0, (s->have_mouse_flag
		  && gfxop_have_mouse(s->gfx_state))? -1 : 0);
}
