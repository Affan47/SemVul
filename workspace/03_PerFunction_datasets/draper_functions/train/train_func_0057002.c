modify_icon_position(
	FvwmWindow *fw, int dx, int dy)
{
	if (fw->icon_g.picture_w_g.width > 0 || HAS_NO_ICON_TITLE(fw))
	{


		fw->icon_g.picture_w_g.x += dx;
		fw->icon_g.picture_w_g.y += dy;
	}
	if (!HAS_NO_ICON_TITLE(fw))
	{
		fw->icon_g.title_w_g.x += dx;
		fw->icon_g.title_w_g.y += dy;
	}

	return;
}
