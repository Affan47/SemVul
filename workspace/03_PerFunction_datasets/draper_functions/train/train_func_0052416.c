taskbar_read_clientlist (taskbar * tb)
{
	Window *win, focus_win;
	int num, i, rev, desk, new_desk = 0;
	task *list, *next;

	desk = get_current_desktop ();
	if (desk != tb->my_desktop)
	{
		new_desk = 1;
		tb->my_desktop = desk;
	}

	XGetInputFocus (dd, &focus_win, &rev);


	win = get_prop_data (root_win, atom__NET_CLIENT_LIST, XA_WINDOW, &num);
	if (!win)
	{

		win = get_prop_data (root_win, atom__WIN_CLIENT_LIST, XA_CARDINAL, &num);
		if (!win)
			return;
	}


	list = tb->task_list;
	while (list)
	{
		list->focused = (focus_win == list->win);
		next = list->next;

		if (!new_desk)
			for (i = num - 1; i >= 0; i--)
				if (list->win == win[i])
					goto dontdel;
		del_task (tb, list->win);
dontdel:

		list = next;
	}


	for (i = 0; i < num; i++)
	{
		if (!find_task (tb, win[i]))
			add_task (tb, win[i], (win[i] == focus_win));
	}

	XFree (win);
}
