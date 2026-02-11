frame_new_width(topfrp, width, leftfirst, wfw)
    frame_T	*topfrp;
    int		width;
    int		leftfirst;
    int		wfw;

{
    frame_T	*frp;
    int		extra_cols;
    int		w;
    win_T	*wp;

    if (topfrp->fr_layout == FR_LEAF)
    {

	wp = topfrp->fr_win;

	for (frp = topfrp; frp->fr_parent != NULL; frp = frp->fr_parent)
	    if (frp->fr_parent->fr_layout == FR_ROW && frp->fr_next != NULL)
		break;
	if (frp->fr_parent == NULL)
	    wp->w_vsep_width = 0;
	win_new_width(wp, width - wp->w_vsep_width);
    }
    else if (topfrp->fr_layout == FR_COL)
    {
	do
	{

	    for (frp = topfrp->fr_child; frp != NULL; frp = frp->fr_next)
	    {
		frame_new_width(frp, width, leftfirst, wfw);
		if (frp->fr_width > width)
		{

		    width = frp->fr_width;
		    break;
		}
	    }
	} while (frp != NULL);
    }
    else
    {


	frp = topfrp->fr_child;
	if (wfw)

	    while (frame_fixed_width(frp))
	    {
		frp = frp->fr_next;
		if (frp == NULL)
		    return;
	    }
	if (!leftfirst)
	{

	    while (frp->fr_next != NULL)
		frp = frp->fr_next;
	    if (wfw)

		while (frame_fixed_width(frp))
		    frp = frp->fr_prev;
	}

	extra_cols = width - topfrp->fr_width;
	if (extra_cols < 0)
	{

	    while (frp != NULL)
	    {
		w = frame_minwidth(frp, NULL);
		if (frp->fr_width + extra_cols < w)
		{
		    extra_cols += frp->fr_width - w;
		    frame_new_width(frp, w, leftfirst, wfw);
		}
		else
		{
		    frame_new_width(frp, frp->fr_width + extra_cols,
							      leftfirst, wfw);
		    break;
		}
		if (leftfirst)
		{
		    do
			frp = frp->fr_next;
		    while (wfw && frp != NULL && frame_fixed_width(frp));
		}
		else
		{
		    do
			frp = frp->fr_prev;
		    while (wfw && frp != NULL && frame_fixed_width(frp));
		}

		if (frp == NULL)
		    width -= extra_cols;
	    }
	}
	else if (extra_cols > 0)
	{

	    frame_new_width(frp, frp->fr_width + extra_cols, leftfirst, wfw);
	}
    }
    topfrp->fr_width = width;
}
