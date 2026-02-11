refresh_menubar(CMENU *menu)
{
	int i;
	QList<QAction *> list;
	QAction *action;
	MyMainWindow *toplevel;
	CWINDOW *window;
	QMenuBar *menuBar;

	if (!CMENU_is_toplevel(menu))
		return;

	toplevel = (MyMainWindow *)(menu->toplevel);
	window = ((CWINDOW *)(menu->parent));
	menuBar = window->menuBar;
	if (!menuBar)
		return;

	list = menuBar->actions();

	for (i = 0; i < list.count(); i++)
	{
		action = list.at(i);
		menu = CMenu::dict[action];
		if (!menu || menu->deleted)
			continue;
		if (action->isVisible() && !action->isSeparator())
			break;
	}

	window->hideMenuBar = i == list.count();

	toplevel->configure();
}
