get_prefered_popup_position(
	MenuRoot *mr, MenuRoot *submenu, int *px, int *py,
	Bool *pprefer_left_submenus)
{
	int menu_x, menu_y;
	MenuItem *mi = NULL;

	if (!menu_get_geometry(
		    mr, &JunkRoot, &menu_x, &menu_y, &JunkWidth, &JunkHeight,
		    &JunkBW, &JunkDepth))
	{
		*px = 0;
		*py = 0;
		*pprefer_left_submenus = False;
		fvwm_msg(ERR, "get_prefered_popup_position",
			 "can't get geometry of menu %s", MR_NAME(mr));
		return;
	}

	*pprefer_left_submenus =
		(MR_HAS_POPPED_UP_LEFT(mr) ||
		 (MST_USE_LEFT_SUBMENUS(mr) &&
		  !MR_HAS_POPPED_UP_RIGHT(mr)));

	if (*pprefer_left_submenus)
	{
		*px = get_left_popup_x_position(mr, submenu, menu_x);
	}
	else
	{
		*px = get_right_popup_x_position(mr, submenu, menu_x);
	}

	if (MR_SELECTED_ITEM(mr))
	{
		mi = MR_SELECTED_ITEM(mr);
	}
	if (mi)
	{
		*py = menu_y + MI_Y_OFFSET(mi) -
			MST_BORDER_WIDTH(mr) + MST_RELIEF_THICKNESS(mr);
	}
	else
	{
		*py = menu_y;
	}
}
