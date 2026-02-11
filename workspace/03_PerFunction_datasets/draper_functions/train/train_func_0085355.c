UpdateRootTransapency(Bool pr_only, Bool do_draw)
{
	Item *item;

	if (CSET_IS_TRANSPARENT(colorset))
	{
		if (CSET_IS_TRANSPARENT_PR_PURE(colorset))
		{
			XClearArea(dpy, CF.frame, 0,0,0,0, False);
			if (do_draw)
			{
				RedrawFrame(NULL);
			}
		}
		else if (!pr_only || CSET_IS_TRANSPARENT_PR(colorset))
		{
			SetWindowBackground(
				dpy, CF.frame, CF.max_width, CF.total_height,
				&Colorset[(colorset)], Pdepth,
				root_item_ptr->header.dt_ptr->dt_GC, False);
			if (do_draw)
			{
				XClearArea(dpy, CF.frame, 0,0,0,0, False);
				RedrawFrame(NULL);
			}
		}
	}
	if (!root_item_ptr->header.next || !CSET_IS_TRANSPARENT(itemcolorset))
	{
		return;
	}
	for (item = root_item_ptr->header.next; item != NULL;
	     item = item->header.next)
	{
		if (item->header.win != None)
		{
			if (CSET_IS_TRANSPARENT_PR(itemcolorset) &&
			    !CSET_IS_TRANSPARENT(colorset))
			{
				continue;
			}
			if (CSET_IS_TRANSPARENT_PR_PURE(itemcolorset))
			{
				XClearArea(
					dpy, item->header.win, 0,0,0,0, False);
				if (do_draw)
				{
					RedrawItem(item, 0, NULL);
				}
			}
			else if (!pr_only ||
				 CSET_IS_TRANSPARENT_PR(itemcolorset))
			{
				SetWindowBackground(
					dpy, item->header.win,
					item->header.size_x, item->header.size_y,
					&Colorset[(itemcolorset)], Pdepth,
					item->header.dt_ptr->dt_GC, False);
				XClearArea(
					dpy, item->header.win, 0,0,0,0, False);
				if (do_draw)
				{
					RedrawItem(item, 0, NULL);
				}
			}
		}
	}
}
