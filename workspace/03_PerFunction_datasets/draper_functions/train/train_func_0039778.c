get_icon_corner(
	FvwmWindow *fw, rectangle *ret_g)
{
	switch (GET_TITLE_DIR(fw))
	{
	case DIR_N:
	case DIR_W:
		ret_g->x = fw->g.frame.x;
		ret_g->y = fw->g.frame.y;
		break;
	case DIR_S:
		ret_g->x = fw->g.frame.x;
		ret_g->y = fw->g.frame.y + fw->g.frame.height -
			ret_g->height;
		break;
	case DIR_E:
		ret_g->x = fw->g.frame.x + fw->g.frame.width -
			ret_g->width;
		ret_g->y = fw->g.frame.y;
		break;
	}

	return;
}
