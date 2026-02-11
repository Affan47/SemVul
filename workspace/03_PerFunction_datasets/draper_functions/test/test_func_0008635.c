draw_obj_to_control_map(state_t *s, gfxw_dyn_view_t *view)
{
	reg_t obj = make_reg(view->ID, view->subID);

	if (!is_object(s, obj))
		SCIkwarn(SCIkWARNING, "View %d does not contain valid object reference "PREG"\n", view->ID, PRINT_REG(obj));

	if (!(view->signalp && (((reg_t *)view->signalp)->offset & _K_VIEW_SIG_FLAG_IGNORE_ACTOR))) {
		abs_rect_t abs_zone = get_nsrect(s, make_reg(view->ID, view->subID), 1);
		draw_rect_to_control_map (s, abs_zone);
	}
}
