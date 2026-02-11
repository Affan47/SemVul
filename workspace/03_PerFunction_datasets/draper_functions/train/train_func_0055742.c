ay_chat_window_raise(chat_window *cw, const char *message)
{
	if (should_window_raise(message)) {
		if (cw->notebook)
			gtk_notebook_set_current_page(GTK_NOTEBOOK(cw->notebook),
						      gtk_notebook_page_num(
							      GTK_NOTEBOOK(cw->notebook),
							      cw->pane));
		gdk_window_raise(cw->window->window);

		return 1;
	}

	return 0;
}
