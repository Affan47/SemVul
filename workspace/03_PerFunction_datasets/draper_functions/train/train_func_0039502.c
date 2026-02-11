__scan_for_pixmap(
	char *name, char type, string_context_t *context)
{
	FvwmPicture *p;
	FvwmPictureAttributes fpa;
	int current_mini_icon;


	current_mini_icon = -999999999;
	switch (type)
	{
	case '@':
		if (SCTX_GET_MR(*context) == NULL)
		{
			abort();
		}
		if (MR_SIDEPIC(SCTX_GET_MR(*context)))
		{
			return False;
		}
		break;
	case '*':

		if (SCTX_GET_MI(*context) == NULL)
		{
			abort();
		}
		if (MI_PICTURE(SCTX_GET_MI(*context)))
		{
			return False;
		}
		break;
	case '%':

		if (SCTX_GET_MI(*context) == NULL)
		{
			abort();
		}
		current_mini_icon  = 0;
		while (current_mini_icon < MAX_MENU_ITEM_MINI_ICONS)
		{
			if (
				MI_MINI_ICON(SCTX_GET_MI(*context))
				[current_mini_icon])
			{
				current_mini_icon++;
			}
			else
			{
				break;
			}
		}
		if (current_mini_icon == MAX_MENU_ITEM_MINI_ICONS)
		{
			return False;
		}
		break;
	default:
		abort();
	}

	fpa.mask = 0;
	p = PCacheFvwmPicture(
		dpy, Scr.NoFocusWin, NULL, name, fpa);
	if (!p)
	{
		fvwm_msg(WARN, "scanForPixmap",
			 "Couldn't load image from %s", name);


		return True;
	}

	switch (type)
	{
	case '@':
		MR_SIDEPIC(SCTX_GET_MR(*context)) = p;

		break;
	case '*':
		MI_PICTURE(SCTX_GET_MI(*context)) = p;
		MI_HAS_PICTURE(SCTX_GET_MI(*context)) = True;

		break;
	case '%':
		MI_MINI_ICON(SCTX_GET_MI(*context))[current_mini_icon] = p;
		MI_HAS_PICTURE(SCTX_GET_MI(*context)) = True;

		break;
	}

	return True;
}
