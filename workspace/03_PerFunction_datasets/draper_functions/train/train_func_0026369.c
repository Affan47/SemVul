PauseScript_action(Widget w _is_unused, XEvent *event _is_unused, String *params _is_unused,
    Cardinal *num_params _is_unused)
{
	if (sms == SN || (sms->type != ST_PEER && sms->type != ST_CHILD)) {
		popup_an_error("%s can only be called from a script",
		    action_name(PauseScript_action));
		return;
	}
	sms->state = SS_PAUSED;
}
