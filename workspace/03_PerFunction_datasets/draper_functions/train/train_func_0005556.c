brasero_audio_disc_button_pressed_cb (GtkTreeView *tree,
				      GdkEventButton *event,
				      BraseroAudioDisc *disc)
{
	GtkWidgetClass *widget_class;


	if (event->window != gtk_tree_view_get_bin_window (GTK_TREE_VIEW (tree)))
		return FALSE;

	widget_class = GTK_WIDGET_GET_CLASS (tree);


	if (event->button == 3) {
		GtkTreeSelection *selection;
		GtkTreePath *path = NULL;
		GtkWidget *widget;

		gtk_tree_view_get_path_at_pos (tree,
					       event->x,
					       event->y,
					       &path,
					       NULL,
					       NULL,
					       NULL);

		selection = gtk_tree_view_get_selection (tree);
		if (!path || !gtk_tree_selection_path_is_selected (selection, path)) {


			widget_class->button_press_event (GTK_WIDGET (tree), event);

			if (!path) {
				GtkTreeSelection *selection;


				selection = gtk_tree_view_get_selection (tree);
				gtk_tree_selection_unselect_all (selection);
			}
		}

		widget = gtk_ui_manager_get_widget (disc->priv->manager, "/ContextMenu/PasteAudio");
		if (widget) {
			if (gtk_clipboard_wait_is_text_available (gtk_clipboard_get (GDK_SELECTION_CLIPBOARD)))
				gtk_widget_set_sensitive (widget, TRUE);
			else
				gtk_widget_set_sensitive (widget, FALSE);
		}

		widget = gtk_ui_manager_get_widget (disc->priv->manager,"/ContextMenu");
		gtk_menu_popup (GTK_MENU (widget),
				NULL,
				NULL,
				NULL,
				NULL,
				event->button,
				event->time);
		return TRUE;
	}
	else if (event->button == 1) {
		gboolean result;
		GtkTreePath *treepath = NULL;

		result = gtk_tree_view_get_path_at_pos (GTK_TREE_VIEW (disc->priv->tree),
							event->x,
							event->y,
							&treepath,
							NULL,
							NULL,
							NULL);


		widget_class->button_press_event (GTK_WIDGET (tree), event);

		if (!treepath) {
			GtkTreeSelection *selection;


			selection = gtk_tree_view_get_selection (tree);
			gtk_tree_selection_unselect_all (selection);
			return FALSE;
		}

		if (!result)
			return FALSE;

		if (disc->priv->selected_path)
			gtk_tree_path_free (disc->priv->selected_path);

		disc->priv->selected_path = treepath;
		brasero_disc_selection_changed (BRASERO_DISC (disc));

		if (event->type == GDK_2BUTTON_PRESS) {
			GList *list;

			list = g_list_prepend (NULL, treepath);
			brasero_audio_disc_edit_song_properties (disc, list);
			g_list_free (list);
		}
	}

	return TRUE;
}
