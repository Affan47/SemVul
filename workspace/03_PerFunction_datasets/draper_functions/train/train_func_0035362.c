get_unshaded_geometry(
	FvwmWindow *fw, rectangle *ret_g)
{
	if (IS_SHADED(fw))
	{
		if (IS_MAXIMIZED(fw))
		{
			*ret_g = fw->g.max;
		}
		else
		{
			*ret_g = fw->g.normal;
		}
		get_relative_geometry(ret_g, ret_g);
	}
	else
	{
		*ret_g = fw->g.frame;
	}

	return;
}
