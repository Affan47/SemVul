SetValues(Widget gcurrent,
			 Widget grequest,
			 Widget gnew,
			 ArgList args,
			 Cardinal *num_args)
{
    Boolean		redisplay = False;
    PullRightGadget	new = (PullRightGadget)gnew;
    PullRightGadget	current = (PullRightGadget)gcurrent;

    if (new->pull_right.menu_name != current->pull_right.menu_name) {
	XtFree(current->pull_right.menu_name);
	if (!new->pull_right.menu_name)
	    new->pull_right.menu = NULL;
	else {
	    new->pull_right.menu_name = XtNewString(new->pull_right.menu_name);
	    new->pull_right.menu = find_menu(new);
	}
    }

    return redisplay;
}
