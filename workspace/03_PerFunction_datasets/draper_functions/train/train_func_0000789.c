__resize_get_dir_from_window(
	int *ret_xmotion, int *ret_ymotion, FvwmWindow *fw, Window context_w)
{
	if (context_w != Scr.Root && context_w != None)
	{
		if (context_w == FW_W_SIDE(fw, 0))
		{
			*ret_ymotion = 1;
		}
		else if (context_w == FW_W_SIDE(fw, 1))
		{
			*ret_xmotion = -1;
		}
		else if (context_w == FW_W_SIDE(fw, 2))
		{
			*ret_ymotion = -1;
		}
		else if (context_w == FW_W_SIDE(fw, 3))
		{
			*ret_xmotion = 1;
		}
		else if (context_w == FW_W_CORNER(fw, 0))
		{
			*ret_xmotion = 1;
			*ret_ymotion = 1;
		}
		else if (context_w == FW_W_CORNER(fw, 1))
		{
			*ret_xmotion = -1;
			*ret_ymotion = 1;
		}
		else if (context_w == FW_W_CORNER(fw, 2))
		{
			*ret_xmotion = 1;
			*ret_ymotion = -1;
		}
		else if (context_w == FW_W_CORNER(fw, 3))
		{
			*ret_xmotion = -1;
			*ret_ymotion = -1;
		}
	}

	return;
}
