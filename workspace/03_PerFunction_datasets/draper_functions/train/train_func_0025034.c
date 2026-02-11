get_right_popup_x_position(MenuRoot *mr, MenuRoot *submenu, int x)
{
	if (MST_USE_LEFT_SUBMENUS(mr))
	{
		return (x + MR_WIDTH(mr) - MST_BORDER_WIDTH(mr));
	}
	else
	{
		return (x + MR_WIDTH(mr) * MST_POPUP_OFFSET_PERCENT(mr) / 100 +
			MST_POPUP_OFFSET_ADD(mr));
	}
}
