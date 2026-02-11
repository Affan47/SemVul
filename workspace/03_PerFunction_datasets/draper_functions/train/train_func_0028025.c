close_rawlog (GtkWidget *wid, server *serv)
{
	if (is_server (serv))
		serv->gui->rawlog_window = 0;
}
