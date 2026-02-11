MouseSelect_action(Widget w, XEvent *event, String *params,
    Cardinal *num_params)
{
	action_debug(MouseSelect_action, event, params, num_params);
	if (check_usage(MouseSelect_action, *num_params, 0, 0) < 0)
		return;
	if (w != *screen)
		return;
	reset_idle_timer();
	if (kybdlock)
		return;
#if defined(X3270_ANSI)
	if (IN_ANSI)
		return;
#endif
	lightpen_select(mouse_baddr(w, event));
}
