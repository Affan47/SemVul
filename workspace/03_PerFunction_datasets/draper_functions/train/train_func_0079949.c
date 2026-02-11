Flip_action(Widget w _is_unused, XEvent *event, String *params,
    Cardinal *num_params)
{
	action_debug(Flip_action, event, params, num_params);
	if (check_usage(Flip_action, *num_params, 0, 0) < 0)
		return;
	reset_idle_timer();
#if defined(X3270_DBCS)
	if (!dbcs)
#endif
	    screen_flip();
}
