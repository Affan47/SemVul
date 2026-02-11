unselect
	(
	bool need_render
	)
	{
	if (selected >= 0)
		{
		selected = -1;
		locate_cx = locate_cy = -1;
		if (need_render)
			{
			render();
			show();
			}
		if (sel_changed)
			(*sel_changed)();
		}
	enable_controls();
	char buf[150];
	if (info_cnt > 0)
		{

		g_snprintf(buf, sizeof(buf), "Chunks %d to %d",
			info[0].num, info[info_cnt - 1].num);
		gtk_statusbar_push(GTK_STATUSBAR(sbar), sbar_sel, buf);
		}
	}
