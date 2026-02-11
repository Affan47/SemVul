set_win_configuration(WinData *win, FvwmPacketBody *body)
{
	win->desknum = body->add_config_data.desk;
	win->x = body->add_config_data.frame_x;
	win->y = body->add_config_data.frame_y;
	win->width = body->add_config_data.frame_width;
	win->height = body->add_config_data.frame_height;
	win->iconified =  IS_ICONIFIED(&(body->add_config_data));
	win->state = (win == fvwm_focus_win) ? FOCUS_CONTEXT : PLAIN_CONTEXT;
	win->geometry_set = 1;
	memcpy(&(win->flags), &(body->add_config_data.flags),
		sizeof(win->flags));
	{
		int wb_x = body->add_config_data.border_width;
		int wb_y = body->add_config_data.border_width;
		int t_w = 2*wb_x;
		int t_h = 2*wb_y;

		if (HAS_TITLE_DIR(win, DIR_N))
		{
			wb_y += body->add_config_data.title_height;
			t_h += body->add_config_data.title_height;
		}
		else if (HAS_TITLE_DIR(win, DIR_W))
		{
			wb_x += body->add_config_data.title_height;
			t_w += body->add_config_data.title_height;
		}
		if (HAS_TITLE_DIR(win, DIR_S))
		{
			t_h += body->add_config_data.title_height;
		}
		if (HAS_TITLE_DIR(win, DIR_E))
		{
			t_w += body->add_config_data.title_height;
		}
		win->real_g.x = win->x + wb_x;
		win->real_g.y = win->y + wb_y;
		win->real_g.width = win->width - t_w;
		win->real_g.height = win->height - t_h;
	}
}
