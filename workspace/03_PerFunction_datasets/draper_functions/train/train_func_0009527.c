mw_entry_buffer_cursor_position_cb (GObject *object, GParamSpec *pspec, AlmanahMainWindow *main_window)
{
	GtkTextIter iter;
	AlmanahMainWindowPrivate *priv = main_window->priv;
	GSList *_tag_list = NULL, *tag_list = NULL;
	gboolean range_selected = FALSE;
	gboolean bold_toggled = FALSE, italic_toggled = FALSE, underline_toggled = FALSE, hyperlink_toggled = FALSE;


	if (priv->updating_formatting == TRUE)
		return;


	range_selected = gtk_text_buffer_get_selection_bounds (priv->entry_buffer, &iter, NULL);
	if (range_selected == FALSE)
		_tag_list = gtk_text_iter_get_tags (&iter);


	priv->updating_formatting = TRUE;

	tag_list = _tag_list;
	while (tag_list != NULL) {
		GtkTextTag *tag;
		gchar *tag_name;
		GtkToggleAction *action = NULL;

		tag = GTK_TEXT_TAG (tag_list->data);
		g_object_get (tag, "name", &tag_name, NULL);


		if (tag_name != NULL) {
			if (strcmp (tag_name, "bold") == 0) {
				action = priv->bold_action;
				bold_toggled = TRUE;
			} else if (strcmp (tag_name, "italic") == 0) {
				action = priv->italic_action;
				italic_toggled = TRUE;
			} else if (strcmp (tag_name, "underline") == 0) {
				action = priv->underline_action;
				underline_toggled = TRUE;
			}
		}


		if (ALMANAH_IS_HYPERLINK_TAG (tag)) {
			action = priv->hyperlink_action;
			hyperlink_toggled = TRUE;
		}

		if (action != NULL) {

			gtk_toggle_action_set_active (action, TRUE);
		} else if (tag_name == NULL || strcmp (tag_name, "gtkspell-misspelled") != 0) {

			g_warning (_("Unknown or duplicate text tag \"%s\" in entry. Ignoring."), tag_name);
		}

		g_free (tag_name);
		tag_list = tag_list->next;
	}

	g_slist_free (_tag_list);

	if (range_selected == FALSE) {

		if (bold_toggled == FALSE)
			gtk_toggle_action_set_active (priv->bold_action, FALSE);
		if (italic_toggled == FALSE)
			gtk_toggle_action_set_active (priv->italic_action, FALSE);
		if (underline_toggled == FALSE)
			gtk_toggle_action_set_active (priv->underline_action, FALSE);

		if (hyperlink_toggled == FALSE) {
			gtk_toggle_action_set_active (priv->hyperlink_action, FALSE);
		}
	}


	priv->updating_formatting = FALSE;
}
