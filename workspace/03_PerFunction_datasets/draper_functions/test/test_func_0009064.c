nautilus_query_editor_handle_event (NautilusQueryEditor *editor,
				    GdkEventKey         *event)
{
	GtkWidget *toplevel;
	GtkWidget *old_focus;
	GdkEvent *new_event;
	gboolean retval;


	if (gtk_widget_has_focus (editor->details->entry)) {
		return FALSE;
	}


	if (event->keyval == GDK_KEY_slash || event->keyval == GDK_KEY_Delete || event->keyval == GDK_KEY_BackSpace) {
		return FALSE;
	}


	if (!gtk_widget_get_visible (GTK_WIDGET (editor)) && event->keyval == GDK_KEY_space) {
		return FALSE;
	}


	if (!g_unichar_isprint (gdk_keyval_to_unicode (event->keyval))) {
		return FALSE;
	}

	if (!gtk_widget_get_realized (editor->details->entry)) {
		gtk_widget_realize (editor->details->entry);
	}

	toplevel = gtk_widget_get_toplevel (GTK_WIDGET (editor));
	if (gtk_widget_is_toplevel (toplevel)) {
		old_focus = gtk_window_get_focus (GTK_WINDOW (toplevel));
	} else {
		old_focus = NULL;
	}


	gtk_widget_grab_focus (editor->details->entry);

	new_event = gdk_event_copy ((GdkEvent *) event);
	g_object_unref (((GdkEventKey *) new_event)->window);
	((GdkEventKey *) new_event)->window = g_object_ref
		(gtk_widget_get_window (editor->details->entry));
	retval = gtk_widget_event (editor->details->entry, new_event);
	gdk_event_free (new_event);

	if (!retval && old_focus) {
		gtk_widget_grab_focus (old_focus);
	}

	return retval;
}
