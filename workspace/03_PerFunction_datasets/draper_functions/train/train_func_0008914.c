kNumLoops(state_t *s, int funct_nr, int argc, reg_t *argv)
{
	reg_t obj = argv[0];
	int view = GET_SEL32V(obj, view);
	int loops_nr = gfxop_lookup_view_get_loops(s->gfx_state, view);


	if (loops_nr < 0) {
		SCIkwarn(SCIkERROR, "view.%d (0x%x) not found\n", view, view);
		return NULL_REG;
	}

	SCIkdebug(SCIkGRAPHICS, "NumLoops(view.%d) = %d\n", view, loops_nr);

	return make_reg(0, loops_nr);
}
