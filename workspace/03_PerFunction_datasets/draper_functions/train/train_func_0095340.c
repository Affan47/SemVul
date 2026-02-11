copy_clipboard_win(gpointer data){
	gchar *str=NULL;
	GtkClipboard* clipboard;

	LOG(LOG_DEBUG, "IN : copy_clipboard()");

#ifdef __WIN32__
	clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
#else
	clipboard = gtk_clipboard_get(GDK_SELECTION_PRIMARY);
#endif

	str = gtk_clipboard_wait_for_text(clipboard);
	if(str == NULL){
		goto END;
	}

	remove_space(str);
	search_selected(str);
	g_free(str);

 END:
	if(selection_mode != SELECTION_DO_NOTHING){
		auto_lookup_start();
	}

	LOG(LOG_DEBUG, "OUT : copy_clipboard()");
	return (FALSE);
}
