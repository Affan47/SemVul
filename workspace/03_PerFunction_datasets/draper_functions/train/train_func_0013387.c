cmd_qall(Filerange *range, enum CmdOpt opt, const char *argv[]) {
	for (EditorWin *next, *win = vis->windows; win; win = next) {
		next = win->next;
		if (!text_modified(vis->win->text->data) || (opt & CMD_OPT_FORCE))
			editor_window_close(win);
	}
	if (!vis->windows)
		quit(NULL);
	else
		info_unsaved_changes();
	return vis->windows == NULL;
}
