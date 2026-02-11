Initialize(Widget grequest, Widget gnew,
		       ArgList args, Cardinal *num_args)
{
    ManagerWidget	new = (ManagerWidget)gnew;

    if (new->core.width  == 0)
	if (new->manager.pref_width == 0)
	    new->core.width  = 1;
	else
	    new->core.width = new->manager.pref_width;
    if (new->core.height == 0)
	if (new->manager.pref_height == 0)
	    new->core.height = 1;
	else
	    new->core.height = new->manager.pref_height;
}
