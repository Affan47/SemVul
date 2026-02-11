on_conf_window_close(ConfWindow* dlg)
{
	g_assert(dlg == confwindow);
	delete confwindow;
	confwindow=NULL;
}
