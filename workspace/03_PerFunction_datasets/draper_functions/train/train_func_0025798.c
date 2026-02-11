kDrawControl(state_t *s, int funct_nr, int argc, reg_t *argv)
{
	reg_t obj = argv[0];

	_k_disable_delete_for_now(s, obj);
	_k_draw_control(s, obj, 0);
	FULL_REDRAW();
	return NULL_REG;
}
