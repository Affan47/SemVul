socket_lock_input_cb(GIOChannel *source, GIOCondition condition, gpointer data)
{
	gint fd, sock;
	gchar buf[BUFFER_LENGTH];
	struct sockaddr_in caddr;
	socklen_t caddr_len = sizeof(caddr);
	GtkWidget *window = data;
	gboolean popup = FALSE;

	fd = g_io_channel_unix_get_fd(source);
	sock = accept(fd, (struct sockaddr *)&caddr, &caddr_len);


	while (socket_fd_gets(sock, buf, sizeof(buf)) != -1)
	{
		if (strncmp(buf, "open", 4) == 0)
		{
			cl_options.readonly = strncmp(buf+4, "ro", 2) == 0;
			while (socket_fd_gets(sock, buf, sizeof(buf)) != -1 && *buf != '.')
			{
				gsize buf_len = strlen(buf);


				if (buf_len > 0 && buf[buf_len - 1] == '\n')
					buf[buf_len - 1] = '\0';

				handle_input_filename(buf);
			}
			popup = TRUE;
		}
		else if (strncmp(buf, "doclist", 7) == 0)
		{
			gchar *doc_list = build_document_list();
			if (NZV(doc_list))
				socket_fd_write_all(sock, doc_list, strlen(doc_list));
			else


				socket_fd_write_all(sock, "\3", 1);
			g_free(doc_list);
		}
		else if (strncmp(buf, "line", 4) == 0)
		{
			while (socket_fd_gets(sock, buf, sizeof(buf)) != -1 && *buf != '.')
			{
				g_strstrip(buf);

				cl_options.goto_line = atoi(buf);
			}
		}
		else if (strncmp(buf, "column", 6) == 0)
		{
			while (socket_fd_gets(sock, buf, sizeof(buf)) != -1 && *buf != '.')
			{
				g_strstrip(buf);

				cl_options.goto_column = atoi(buf);
			}
		}
#ifdef G_OS_WIN32
		else if (strncmp(buf, "window", 6) == 0)
		{
			HWND hwnd = (HWND) gdk_win32_drawable_get_handle(
				GDK_DRAWABLE(gtk_widget_get_window(window)));
			socket_fd_write(sock, (gchar *)&hwnd, sizeof(hwnd));
		}
#endif
	}

	if (popup)
	{
#ifdef GDK_WINDOWING_X11


		gdk_x11_window_set_user_time(gtk_widget_get_window(window),
			gdk_x11_get_server_time(gtk_widget_get_window(window)));
#endif
		gtk_window_present(GTK_WINDOW(window));
#ifdef G_OS_WIN32
		gdk_window_show(gtk_widget_get_window(window));
#endif
	}

	socket_fd_close(sock);

	return TRUE;
}
