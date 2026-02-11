source_remove_clicked_cb (GtkWidget       *widget,
			  GdictPrefDialog *dialog)
{
  GtkTreeSelection *selection;
  GtkTreeModel *model;
  GtkTreeIter iter;
  gboolean is_selected;
  gchar *name, *description;

  selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (dialog->sources_view));
  if (!selection)
    return;

  is_selected = gtk_tree_selection_get_selected (selection, &model, &iter);
  if (!is_selected)
    return;

  gtk_tree_model_get (model, &iter,
  		      SOURCES_NAME_COLUMN, &name,
  		      SOURCES_DESCRIPTION_COLUMN, &description,
  		      -1);
  if (!name)
    return;
  else
    {
      GtkWidget *confirm_dialog;
      gint response;

      confirm_dialog = gtk_message_dialog_new (GTK_WINDOW (dialog),
      					       GTK_DIALOG_DESTROY_WITH_PARENT,
      					       GTK_MESSAGE_WARNING,
      					       GTK_BUTTONS_NONE,
      					       _("Remove \"%s\"?"), description);
      gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (confirm_dialog),
      						_("This will permanently remove the "
      						  "dictionary source from the list."));

      gtk_dialog_add_button (GTK_DIALOG (confirm_dialog),
      			     GTK_STOCK_CANCEL,
      			     GTK_RESPONSE_CANCEL);
      gtk_dialog_add_button (GTK_DIALOG (confirm_dialog),
      			     GTK_STOCK_REMOVE,
      			     GTK_RESPONSE_OK);

      gtk_window_set_title (GTK_WINDOW (confirm_dialog), "");

      response = gtk_dialog_run (GTK_DIALOG (confirm_dialog));
      if (response == GTK_RESPONSE_CANCEL)
        {
          gtk_widget_destroy (confirm_dialog);

          goto out;
        }

      gtk_widget_destroy (confirm_dialog);
    }

  if (gdict_source_loader_remove_source (dialog->loader, name))
    gtk_list_store_remove (GTK_LIST_STORE (model), &iter);
  else
    {
      GtkWidget *error_dialog;
      gchar *message;

      message = g_strdup_printf (_("Unable to remove source '%s'"),
      				 description);

      error_dialog = gtk_message_dialog_new (GTK_WINDOW (dialog),
      					     GTK_DIALOG_DESTROY_WITH_PARENT,
      					     GTK_MESSAGE_ERROR,
      					     GTK_BUTTONS_OK,
      					     "%s", message);
      gtk_window_set_title (GTK_WINDOW (error_dialog), "");

      gtk_dialog_run (GTK_DIALOG (error_dialog));

      gtk_widget_destroy (error_dialog);
    }

out:
  g_free (name);
  g_free (description);

  update_sources_view (dialog);
}
