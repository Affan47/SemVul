get_icon_picture_geometry(
	FvwmWindow *fw, rectangle *ret_g)
{
	if (fw->icon_g.picture_w_g.width == 0)
	{
		memset(ret_g, 0, sizeof(*ret_g));
		return False;
	}
	*ret_g = fw->icon_g.picture_w_g;

	return True;
}
