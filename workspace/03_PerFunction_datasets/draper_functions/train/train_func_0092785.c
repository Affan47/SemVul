tab_completion_popup_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	TabCompData *td = data;

	if (event->keyval == GDK_Tab ||
	    event->keyval == GDK_BackSpace ||
	    (event->keyval >= 0x20 && event->keyval <= 0xFF) )
		{
		if (event->keyval >= 0x20 && event->keyval <= 0xFF)
			{
			gchar buf[2];
			gint p = -1;

			buf[0] = event->keyval;
			buf[1] = '\0';
			gtk_editable_insert_text(GTK_EDITABLE(td->entry), buf, 1, &p);
			gtk_editable_set_position(GTK_EDITABLE(td->entry), -1);


			td->choices = 0;
			gtk_container_foreach(GTK_CONTAINER(widget), tab_completion_iter_menu_items, (gpointer) td);
			if (td->choices > 1) return TRUE;
			if (td->choices > 0) tab_completion_do(td);
			}


		gtk_menu_popdown(GTK_MENU(widget));

#if GTK_CHECK_VERSION(2,12,0)
		g_object_unref(widget);
#else
		gtk_widget_unref(widget);
#endif
		return TRUE;
		}

	return FALSE;
}
