editor_window_prev(Editor *ed) {
	EditorWin *sel = ed->win;
	if (!sel)
		return;
	ed->win = ed->win->prev;
	if (!ed->win)
		for (ed->win = ed->windows; ed->win->next; ed->win = ed->win->next);
	ed->ui->window_focus(ed->win->ui);
}
