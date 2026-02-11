action_list_up(Widget w, XEvent *event,
		    String *params, Cardinal *no_params)
{
    long	step = 1;

    if (global.busy)
	return;

    if (no_params && *no_params == 1 &&
	params[0][0] >= '0' && params[0][0] <= '9')
	if (!strchr(params[0], '.'))
	    step = atol(params[0]);
	else {
	    step = ScrollableGetVShown(global.mode == NewsModeGroup ?
				       main_widgets.thread_list :
				       main_widgets.group_list);
	    step *= atof(params[0]);
	}

    do_list(-step);
}
