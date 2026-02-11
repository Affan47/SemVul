pot2surf_select_instruc_file_to_save()
{
  GtkFileFilter *filter_instruc;
  GtkFileFilter *filter_none;
  GtkWidget* file_chooser;
  char *directory = visu_ui_getLastOpenDirectory();
  int n=0;
  const gchar *pot_file = gtk_entry_get_text(GTK_ENTRY(pot2surf_entry_source_pot_file));
  const gchar *surf_file = gtk_entry_get_text(GTK_ENTRY(pot2surf_entry_target_surf_file));
  GString *default_file = NULL;

  gtk_tree_model_foreach(GTK_TREE_MODEL(pot2surf_list_store), pot2surf_count_surf, &n);
  if(n == 0)
    {
      visu_ui_raiseWarning(_("Saving a file"),
			   _("Please specify surfaces to draw"), (GtkWindow*)0);
      return;
    }
  if(strcmp(pot_file, "") == 0)
    {
      visu_ui_raiseWarning(_("Saving a file"),
			   _("Please select a source pot file"), (GtkWindow*)0);
      return;
    }
  if(surf_file == NULL || strcmp(surf_file, "") == 0)
    {
      visu_ui_raiseWarning(_("Saving a file"),
			   _("Please select a target surf file"), (GtkWindow*)0);
      return;
    }

  default_file = g_string_new("");
  g_string_append(default_file, pot_file);
  g_string_append(default_file, ".instruc");

  filter_instruc = gtk_file_filter_new ();
  filter_none = gtk_file_filter_new();
  file_chooser = gtk_file_chooser_dialog_new("Save as a .instruc file", GTK_WINDOW(convert_window),
					     GTK_FILE_CHOOSER_ACTION_SAVE,
					     GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					     GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, NULL);
  if(directory)
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(file_chooser), directory);

  gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(file_chooser),default_file->str);

  gtk_file_filter_add_pattern(filter_instruc, "*.instruc");
  gtk_file_filter_set_name(filter_instruc, "Instruction files (*.instruc)");
  gtk_file_chooser_add_filter (GTK_FILE_CHOOSER(file_chooser), filter_instruc);

  gtk_file_filter_add_pattern(filter_none, "*");
  gtk_file_filter_set_name(filter_none, "All files");
  gtk_file_chooser_add_filter (GTK_FILE_CHOOSER(file_chooser), filter_none);

  while(1)
    switch(gtk_dialog_run(GTK_DIALOG(file_chooser)))
      {
      case GTK_RESPONSE_ACCEPT:
	if(!pot2surf_build_instruc_file(pot_file, surf_file,
					gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser)), n))

	  break;
	visu_ui_setLastOpenDirectory(gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER (file_chooser)), VISU_UI_DIR_SURFACE);
	g_string_free(default_file, TRUE);
	gtk_widget_destroy(file_chooser);
	return;
      case GTK_RESPONSE_CANCEL:
      default:
	g_string_free(default_file, TRUE);
	gtk_widget_destroy (file_chooser);
	return;
      }
}
