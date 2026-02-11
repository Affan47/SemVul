save (GladeWindow *window, GladeProject *project, const gchar *path)
{
  gchar *display_name;
  time_t mtime;
  GtkWidget *dialog;
  GtkWidget *button;
  gint response;

  if (check_loading_project_for_save (project))
    return;


  if (glade_project_get_path (project))
    {
      mtime = glade_util_get_file_mtime (glade_project_get_path (project), NULL);

      if (mtime > glade_project_get_file_mtime (project))
	{

	  dialog = gtk_message_dialog_new (GTK_WINDOW (window),
					   GTK_DIALOG_MODAL,
					   GTK_MESSAGE_WARNING,
					   GTK_BUTTONS_NONE,
					   _("The file %s has been modified since reading it"),
					   glade_project_get_path (project));

	  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog),
						    _("If you save it, all the external changes could be lost. "
						      "Save it anyway?"));

	  gtk_window_set_title (GTK_WINDOW (dialog), "");

	  button = gtk_button_new_with_mnemonic (_("_Save Anyway"));
	  gtk_button_set_image (GTK_BUTTON (button),
				gtk_image_new_from_stock (GTK_STOCK_SAVE,
							  GTK_ICON_SIZE_BUTTON));
	  gtk_widget_show (button);

	  gtk_dialog_add_action_widget (GTK_DIALOG (dialog), button,
					GTK_RESPONSE_ACCEPT);
	  gtk_dialog_add_button (GTK_DIALOG (dialog), _("_Don't Save"),
				 GTK_RESPONSE_REJECT);

	  gtk_dialog_set_default_response (GTK_DIALOG (dialog),
					   GTK_RESPONSE_REJECT);

	  response = gtk_dialog_run (GTK_DIALOG (dialog));

	  gtk_widget_destroy (dialog);

	  if (response == GTK_RESPONSE_REJECT)
	    return;
	}
    }


  if (!do_save (window, project, path))
    return;


  display_name = glade_project_get_name (project);

  recent_add (window, glade_project_get_path (project));
  update_default_path (window, glade_project_get_path (project));


  refresh_title (window);
  refresh_projects_list_item (window, project);
  refresh_notebook_tab_for_project (window, project);

  glade_util_flash_message (window->priv->statusbar,
                            window->priv->statusbar_actions_context_id,
                            _("Project '%s' saved"), display_name);

  g_free (display_name);
}
