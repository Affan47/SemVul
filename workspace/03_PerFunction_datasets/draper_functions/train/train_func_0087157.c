cmd_vsplit(Filerange *range, enum CmdOpt opt, const char *argv[]) {
	editor_windows_arrange(vis, UI_LAYOUT_VERTICAL);
	if (!argv[1])
		return vis_window_split(vis->win);
	return openfiles(&argv[1]);
}
